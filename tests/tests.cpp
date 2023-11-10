#include "../gs.hpp"
#include <gtest/gtest.h>

TEST(GrayScottTestSuite, ParameterTypeCheck) {
    ASSERT_EQ(typeid(F).name(), typeid(u[0][0]).name());
    ASSERT_EQ(typeid(k).name(), typeid(v[0][0]).name());
    ASSERT_EQ(typeid(F).name(), typeid(k).name());
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