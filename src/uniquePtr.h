#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <iostream>
#include "deleter.h"


template <typename T, typename Deleter = DefaultDeleter<T>>
class UniquePtr {
public:
  UniquePtr() noexcept : m_ptr(nullptr) {
    std::cout << "calling constructor\n";
  }
  UniquePtr(T* ptr) noexcept : m_ptr(ptr) {
     ptr = nullptr;
  }
  UniquePtr(T* ptr, Deleter deleter) noexcept : m_ptr(ptr), m_deleter(deleter) {}
  ~UniquePtr() {
    if(m_ptr != nullptr) {
      m_deleter(m_ptr);
    }
    std::cout << "calling destructor\n";
  }
  //we delete copy, as this should not be allowed
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr &operator=(const UniquePtr&) = delete;
  //move constructors
  UniquePtr(UniquePtr&& other) noexcept : m_ptr(nullptr) {
    this->swap(other);
  }
  UniquePtr &operator=(UniquePtr&& other) noexcept {
    this->swap(other);//https://codereview.stackexchange.com/questions/163854/my-implementation-for-stdunique-ptr
    return *this;//I found here that std::move instead of std::swap can cause memory leak if this != nullptr
  }

  void swap(UniquePtr<T>& other) noexcept {
    std::swap(m_ptr, other.m_ptr);
  }

  T* operator->() const noexcept {return m_ptr;}
  T& operator*() const noexcept {return *m_ptr;}

  void makeUnique(T value){
    m_ptr = new T(value);
  }

  T* get() {
    return m_ptr;
  }

  void reset(T* ptr) {
    m_deleter(m_ptr);
    m_ptr = ptr;
  }

  inline void release(void) noexcept {
      m_ptr = nullptr;
  }

  explicit operator bool() const {
    return (m_ptr != nullptr) ? true : false;
  }

private:
  T *m_ptr = nullptr;
  Deleter m_deleter = Deleter();
};

#endif

