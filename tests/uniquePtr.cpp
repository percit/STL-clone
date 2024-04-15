#include <gtest/gtest.h>
#include "uniquePtr.h"

TEST(MyTestSuite, TestOnePlusOne)
{
  UniquePtr<int> p;
  p.makeUnique(42);
  ASSERT_NE(p.get(), nullptr);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
