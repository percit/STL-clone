#include <gtest/gtest.h>
#include "sharedPtr.h"


TEST(MathTest, AddTest)
{
  SharedPtr<int> p;
  p.makeShared(42);
  ASSERT_NE(p.get(), nullptr);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
