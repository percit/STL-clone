#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
/*
    Ownership: Like unique_ptr, your implementation should enforce exclusive ownership of the managed resource. This means that only one
    unique_ptr should be able to manage the resource at any given time.

    Resource Management: Your implementation should be responsible for managing the lifetime of the dynamically allocated resource. 
    This includes properly deallocating the resource when the unique_ptr goes out of scope or is reset.

    Move Semantics: Implement move semantics to allow transferring ownership of the resource from one unique_ptr to another efficiently.
    This typically involves implementing a move constructor and a move assignment operator.

    Custom Deleter: Optionally, you can support custom deleters to allow users to specify custom cleanup behavior for the managed resource.

    No Copying: Like the standard unique_ptr, your implementation should disable copying to enforce exclusive ownership. This is
    typically done by deleting the copy constructor and copy assignment operator.

    Pointer-like Interface: Your unique_ptr should provide a pointer-like interface, allowing users to access the managed resource 
    through member functions like get() and operator->().

    Destructor: Ensure that the destructor properly releases the managed resource, if any, when the unique_ptr goes out of scope.
*/


//copy assigment and copy constructor must be deleted
//there must be move and move assigment
//there should be delete ptr on destructor
//you should add type traits, or sfinae or other template mechanisms just to try them out, just add some cout to them, to know you calling
//the good functions

#include <iostream>
template <typename T>
class UniquePtr {
public:
  UniquePtr() {
    std::cout << "calling constructor\n";
  }
  ~UniquePtr() {//here we delete
    if(ptr != nullptr) {
      delete ptr;
    }
    std::cout << "calling destructor\n";
  }
  //we delete copy, as this should not be allowed
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr &operator=(const UniquePtr&) = delete;
  //move constructors
  UniquePtr(UniquePtr&& other): ptr(std::move(other->ptr)) {}
  UniquePtr &operator=(UniquePtr&& other) {
    ptr = std::move(other->ptr);
    return *this;
  }

//other functions

  void makeUnique(T value){
    ptr = new T(value);
  }

  T* get() {
    return ptr;
  }

  //here should be a custom deleter
private:
  T *ptr = nullptr;
};

#endif
































