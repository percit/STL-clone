#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H


//constructor from derieved type 
//casting to bool
//checking if empty
//guaranteeing delete on construction failure
//you should add type traits, or sfinae or other template mechanisms just to try them out, just add some cout to them, to know you calling
//the good functions

template <typename T>
struct DefaultDeleter {
  DefaultDeleter() = default;
  DefaultDeleter(const DefaultDeleter& other) = default;
  void operator()(T* ptr) const {delete ptr;}//using m_deleter with () overload and using it as deleter
};


#include <iostream>
template <typename T, typename Deleter = DefaultDeleter<T>>
class UniquePtr {
public:
  UniquePtr(): m_ptr(nullptr) {
    std::cout << "calling constructor\n";
  }
  UniquePtr(T* ptr): m_ptr(ptr) {
     ptr = nullptr;
  }
  UniquePtr(T* ptr, Deleter deleter): m_ptr(ptr), m_deleter(deleter) {}
  ~UniquePtr() {//here we delete
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
};

#endif

