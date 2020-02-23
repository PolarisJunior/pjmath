#include <gtest/gtest.h>
#include "vector3.hpp"

using namespace pjmath;

TEST(PJ_MATH_TEST, VECTOR3_TEST) {
  EXPECT_EQ(Vector3::one + Vector3::one, Vector3(2, 2, 2));

  EXPECT_EQ(-Vector3::one, Vector3(-1, -1, -1));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}