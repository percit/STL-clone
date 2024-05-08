#include <iostream>
#include "uniquePtr.h"
#include "sharedPtr.h"


class MyClass {
public:
    void foo() {
        std::cout << "MyClass::foo()" << std::endl;
    }
};
int main()
{
    std::cout << "Program starts" << std::endl;
    UniquePtr<int> p;
    p.makeUnique(1);


   




    //aliasing constructor example:
    SharedPtr<MyClass> ptr1(new MyClass());
    SharedPtr<MyClass> ptr2(ptr1, new MyClass());
    ptr2->foo(); // Calls MyClass::foo()

    std::cout << "Program ends";
    return 0;
}
