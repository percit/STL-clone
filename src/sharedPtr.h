#ifndef SHARED_PTR_H
#define SHARED_PTR_H


#include <iostream>
#include "deleter.h"

template <typename T, typename Deleter = DefaultDeleter<T>>
class SharedPtr {
public:
  SharedPtr() noexcept : m_ptr(nullptr) {
    std::cout << "calling constructor\n";
  }
  SharedPtr(T* ptr) noexcept : m_ptr(ptr), m_refCount(1) {
     ptr = nullptr;
  }
  //constructor with custom deleter
  SharedPtr(T* ptr, Deleter deleter) noexcept : m_ptr(ptr), m_refCount(1), m_deleter(deleter) {}
  //aliasing constructor
  template< class Y >
  SharedPtr(const SharedPtr<Y>& other, T* ptr ) noexcept : m_ptr(ptr), m_refCount(other.m_refCount) {
    if(other.m_ptr != nullptr) {
      m_refCount++;
    }
  }
  ~SharedPtr() {//here we delete
    cleanUp();
    std::cout << "calling destructor\n";
  }
  //copy constructors
  SharedPtr(const SharedPtr& other) noexcept {
    m_ptr = other.m_ptr;
    m_refCount = other.m_refCount;
    if(other.m_ptr != nullptr) {
      m_refCount++;
    }
  }
  SharedPtr &operator=(const SharedPtr& other) noexcept {
    cleanUp();
    m_ptr = other.m_ptr;
    m_refCount = other.m_refCount;
    if(other.m_ptr != nullptr) {
      m_refCount++;
    }
  }
  //move constructors
  SharedPtr(SharedPtr&& other) noexcept : m_ptr(nullptr) {
    this->swap(other);
    other.m_refCount = 0;
  }
  SharedPtr &operator=(SharedPtr&& other) noexcept {
    cleanUp();
    this->swap(other);
    other.m_refCount = 0;
    return *this;
  }

  void swap(SharedPtr<T>& other) noexcept {
    using std::swap;
    swap(m_ptr, other->m_ptr);
  }

  T* operator->() const noexcept {return m_ptr;}
  T& operator*() const noexcept {return *m_ptr;}

  void makeShared(T value){
    m_ptr = new T(value);
    m_refCount++;
  }

  T* get() {
    return m_ptr;
  }

  void reset(T* ptr) {
    m_deleter(m_ptr);
    m_ptr = ptr;
  }

  unsigned int getCount() const {
    return m_refCount;
  }

private:
  void cleanUp() {
    m_refCount--;
    if(m_refCount == 0) {
      if(m_ptr != nullptr) {
        m_deleter(m_ptr);
      }
    }
  }

private:
  T *m_ptr = nullptr;
  Deleter m_deleter = Deleter();
  unsigned int m_refCount = 0;
};

#endif


