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
    if(m_ptr != nullptr) {
      delete m_ptr;
    }
    std::cout << "calling destructor\n";
  }
  //we delete copy, as this should not be allowed
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr &operator=(const UniquePtr&) = delete;
  //move constructors
  UniquePtr(UniquePtr&& other) noexcept : m_ptr(std::move(other->m_ptr)) {}
  UniquePtr &operator=(UniquePtr&& other) noexcept {
    if(this == other) return *this;
    m_ptr = std::move(other->m_ptr);
    return *this;
  }

//other functions

  void makeUnique(T value){
    m_ptr = new T(value);
  }

  T* get() {
    return m_ptr;
  }

  //here should be a custom deleter
private:
  T *m_ptr = nullptr;
};

#endif
































