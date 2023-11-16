#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cmath>
#include <sys/stat.h>

// Define simulation parameters
const int width = 256;                // Width of the grid
const int height = 256;               // Height of the grid
double Du = 0.14;                     // Diffusion rate of U
double Dv = 0.07;                     // Diffusion rate of V
double F = 0.03;                      // Feed rate
double k = 0.0648;                    // Kill rate
double threshold = 0.1;
const double dt = 0.06;               // Time step
const int numIterations = 10000;
const int outputInterval =  100;      // Output every 1000 iterations

// Global variables for output directory creation
bool created = false;
std::string dir = "output/output_files_0";

// Initialize grid and constants
std::vector<std::vector<double>> u(width, std::vector<double>(height, 1.0));
std::vector<std::vector<double>> v(width, std::vector<double>(height, 0.0));

// initialization function
void init() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            u[x][y] = 1.0;
            if (x >= 100 && x <= 200 && y >= 100 && y <= 150){
              v[x][y] = (std::rand() % 100 - 0) / 100.0;  // Random ~ U[0.0,1.0)
            }else{
              v[x][y] = 0.0;
            }
        }
    }
}

// Function to create a directory for output
void createDirectory(const char *dir) {
    // Have to do it like this because we are creating 
    // nested directories
    std::string mkdirCommand = "mkdir -p ";
    mkdirCommand += dir;

    if (system(mkdirCommand.c_str()) != 0) {
        std::cerr << "Error creating directory " << dir << ", try re-running the program." << std::endl;
        return;
    }

    std::cout << "Created output file directory: " << dir << std::endl;
}

// Function to create the name/path of the output directory
std::string createPath(int folderNum) {
    std::stringstream ss;
    ss << "output/output_files_" << folderNum;
    return ss.str();
}

// Function to write the u array to a VTK file
void writeVTKFile(int iteration) {
    std::stringstream ss;
    
    struct stat sb;

    // This if statement will only be entered once due to
    // the global variable created, so only one output_files
    // folder is created per run
    if(!created && stat(dir.c_str(), &sb) == 0 && (sb.st_mode & S_IFDIR)) {
        int folderNum = 0;

        while(true) {
            // Generate folder name using current folderNum
            std::string folderPath = createPath(folderNum);

            // If it does not exist we can create a directory
            // using folderPath
            if (stat(folderPath.c_str(), &sb) != 0) {
                createDirectory(folderPath.c_str());
                dir = folderPath;
                created = true;
                break;
            }

            folderNum++;
        }
    } 
    // this only happens if output_files_0 does not exist
    else if(!created) {
        createDirectory(dir.c_str());
        created = true;
    }

    ss << dir << "/output_" << iteration << ".vtk";
    std::ofstream vtkFile(ss.str());
    vtkFile << "# vtk DataFile Version 3.0\n";
    vtkFile << "Gray-Scott Simulation Output\n";
    vtkFile << "ASCII\n";
    vtkFile << "DATASET STRUCTURED_POINTS\n";
    vtkFile << "DIMENSIONS " << width << " " << height << " 1\n";
    vtkFile << "SPACING 1.0 1.0 1.0\n";
    vtkFile << "ORIGIN 0 0 0\n";
    vtkFile << "POINT_DATA " << width * height << "\n";
    vtkFile << "SCALARS u double\n";
    vtkFile << "LOOKUP_TABLE default\n";

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            vtkFile << v[x][y] << " ";
        }
        vtkFile << "\n";
    }

    vtkFile.close();
}


// Function to perform one time step of the simulation
void simulateStep() {

    std::vector<std::vector<double>> nextU = u;
    std::vector<std::vector<double>> nextV = v;

    double laplaceU = 0.0, laplaceV = 0.0, dU = 0.0, dV = 0.0;
    double a, b;
    for (int x = 1; x < width - 1; ++x) {
        for (int y = 1; y < height - 1; ++y) {
            
            a = u[x][y];
            b = v[x][y];
            
            laplaceU = (u[x + 1][y] + u[x - 1][y] + u[x][y + 1] + u[x][y - 1] - 4 * a);
            laplaceV = (v[x + 1][y] + v[x - 1][y] + v[x][y + 1] + v[x][y - 1] - 4 * b);
            
            dU = Du * laplaceU - a * b * b + F * (1.0 - a);
            dV = Dv * laplaceV + a * b * b - (F + k) * b;
            
            nextU[x][y] = a + dt * dU;
            nextV[x][y] = b + dt * dV;
        }
    }

    u = nextU;
    v = nextV;
}

// Function to count elements above a threshold in a 2D vector
double countElementsAboveThreshold(double threshold) {
    int count = 0;
    for (const auto& row : v) {
        for (const double& element : row) {
            if (element > threshold) {
                count++;
            }
        }
    }
    return (double)(count)/(width*height);
}