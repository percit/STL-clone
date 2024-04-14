#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H


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
    if(this == other) return *this;
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
































