#include <gtest/gtest.h>
#include "uniquePtr.h"

TEST(MyTestSuite, TestMakeUnique)
{
  UniquePtr<int> p;
  p.makeUnique(8);
  ASSERT_NE(p.get(), nullptr);
}

TEST(MyTestSuite, TestNewConstructor)
{
  UniquePtr<int> p(new int{ 8 });
  ASSERT_EQ(*p.get(), 8);
}

TEST(MyTestSuite, TestDeleteCopy)
{
  static_assert(!std::is_copy_constructible_v<UniquePtr<int>>, "Copy construction is not allowed");
  static_assert(!std::is_copy_assignable_v<UniquePtr<int>>, "Copy assignment is not allowed");
}

TEST(MyTestSuite, TestUseMove)
{
	UniquePtr<int> p1(new int{8});
	UniquePtr<int> p2 = nullptr;

	p2 = std::move(p1);
  ASSERT_EQ(*p2.get(), 8);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
