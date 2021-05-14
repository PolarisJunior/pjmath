
#include <gtest/gtest.h>
#include <pjmath/divisors.hpp>

using namespace pjmath;

TEST(divisors, usage)
{
  EXPECT_EQ(divisorsOf(24).size(), 8);
  EXPECT_EQ(properDivisorsOf(24).size(), 6);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}