#include <gtest/gtest.h>
#include "sharedPtr.h"


TEST(MathTest, AddTest)
{
  SharedPtr<int> p;
  p.makeShared(42);
  ASSERT_NE(p.get(), nullptr);
}
TEST(MyTestSuite, TestMakeShared)
{
  SharedPtr<int> p;
  p.makeShared(8);
  ASSERT_NE(p.get(), nullptr);
}

TEST(MyTestSuite, TestNewConstructor)
{
  SharedPtr<int> p(new int{ 8 });
  ASSERT_EQ(*p.get(), 8);
}

TEST(MyTestSuite, TestUseMove)
{
	SharedPtr<int> p1(new int{8});
	SharedPtr<int> p2 = nullptr;

	p2 = std::move(p1);
  ASSERT_EQ(*p2.get(), 8);
}

TEST(MyTestSuite, TestAliasingConstructor)
{
  class MyClass {
  public:
      int foo() {
          return 8;
      }
  };

  SharedPtr<MyClass> ptr1(new MyClass());
  SharedPtr<MyClass> ptr2(ptr1, new MyClass());
  ASSERT_EQ(ptr2->foo(), 8);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
