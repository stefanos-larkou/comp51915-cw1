#include "../sim/gs.hpp"
#include <gtest/gtest.h>

// Test (0.1) Check that the type of the model parameters (F, k) 
// matches that of the element type of the u and v vectors
TEST(GrayScottTestSuite, ParameterTypeCheck) {
    ASSERT_EQ(typeid(F).name(), typeid(u[0][0]).name());
    ASSERT_EQ(typeid(k).name(), typeid(v[0][0]).name());
    ASSERT_EQ(typeid(F).name(), typeid(k).name());
}

// Test (0.2) Check that the variables u and v are the same size
TEST(GrayScottTestSuite, VectorSizeCheck) {
    // Check that u and v have the same number of rows
    ASSERT_EQ(u.size(), v.size());

    // Check that u and v have the same number of columns in each row
    for (size_t i = 0; i < u.size(); i++) {
        ASSERT_EQ(u[i].size(), v[i].size());
    }
}

// (0.3) Check that the simulation produces the mathematically 
// correct answer when u = 0 and v = 0.
TEST(GrayScottTestSuite, CorrectResultsCheck) {
    // Have to zero the vectors this way and not like in the header 
    // file because ASSERT_EQ doesn't like that
    for (auto &row : u) {
        std::fill(row.begin(), row.end(), 0.0);
    }

    for (auto &row : v) {
        std::fill(row.begin(), row.end(), 0.0);
    }

    // If u and v are 0, then by the end they will still be 0,
    // so the expected values for u and v are the same as the
    // initial ones
    std::vector<std::vector<double>> expected_u = u;
    std::vector<std::vector<double>> expected_v = v;
    
    // We run the simulation to update u and v
    // No point in running the entire simulation, if u and v
    // are correct after one step then they will be for all steps
    // if not, then the simulation is already going wrong
    simulateStep();

    // Given that u and v are 0, laplace is 0 for both
    // Given that u, v, and laplace are 0, dv is 0,
    // but dU is dt * F (because of the final part
    // of the equation dt * F * (1.0 - u[x][y]), i.e.,
    // dt * F * (1.0 - 0) = dt * F * 1.0 = dt * F
    for (int x = 1; x < width - 1; ++x) {
        for (int y = 1; y < height - 1; ++y) {
            expected_u[x][y] = dt * F;
        }
    }
   
    ASSERT_EQ(u, expected_u);
    ASSERT_EQ(v, expected_v);
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cout << "Usage: " << argv[0] << " <Du> <Dv> <F> <k> <threshold>" << std::endl;
        std::cout << "Parameter values not provided, using default values instead." << std::endl;
    }
    else {
      Du = std::stod(argv[1]);
      Dv = std::stod(argv[2]);
      F = std::stod(argv[3]);
      k = std::stod(argv[4]);
      threshold = std::stod(argv[5]);
    }
       
    init();

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}