#include <iostream>
#include "uniquePtr.h"
#include "sharedPtr.h"

int main()
{
    std::cout << "Program starts" << std::endl;
    UniquePtr<int> p;
    p.makeUnique(1);


    std::cout << "Program ends";
    return 0;
}
