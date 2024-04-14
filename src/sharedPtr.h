#ifndef SHARED_PTR_H
#define SHARED_PTR_H


//add counter which should go up when I use copy constructors (I think)

template <typename T>
struct DefaultDeleter {
  DefaultDeleter() = default;
  DefaultDeleter(const DefaultDeleter& other) = default;
  void operator()(T* ptr) const {delete ptr;}//using m_deleter with () overload and using it as deleter
};


#include <iostream>
template <typename T, typename Deleter = DefaultDeleter<T>>
class SharedPtr {
public:
  SharedPtr(): m_ptr(nullptr) {
    std::cout << "calling constructor\n";
  }
  SharedPtr(T* ptr): m_ptr(ptr) {
     ptr = nullptr;
  }
  SharedPtr(T* ptr, Deleter deleter): m_ptr(ptr), m_deleter(deleter) {}
  ~SharedPtr() {//here we delete
    if(m_ptr != nullptr) {
      m_deleter(m_ptr);
    }
    std::cout << "calling destructor\n";
  }
  //we delete copy, as this should not be allowed
  SharedPtr(const SharedPtr& other) {
    m_ptr = other.m_ptr;
    m_refCount = other.m_refCount;
    if(other.m_ptr != nullptr) {
      m_refCount++;
    }
  }
  SharedPtr &operator=(const SharedPtr& other) {
    m_ptr = other.m_ptr;
    m_refCount = other.m_refCount;
    if(other.m_ptr != nullptr) {
      m_refCount++;
    }
  }
  //move constructors
  SharedPtr(SharedPtr&& other) noexcept : m_ptr(nullptr) {
    this->swap(other);
  }
  SharedPtr &operator=(SharedPtr&& other) noexcept {
    this->swap(other);
    return *this;
  }

  void swap(SharedPtr<T>& other) noexcept {
    using std::swap;
    swap(m_ptr, other->m_ptr);
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

  //here should be a custom deleter
private:
  T *m_ptr = nullptr;
  Deleter m_deleter = Deleter();
  unsigned int m_refCount = 0;
};

#endif


