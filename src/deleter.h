#ifndef DELETER_H
#define DELETER_H


template <typename T>
struct DefaultDeleter {
  DefaultDeleter() = default;
  DefaultDeleter(const DefaultDeleter& other) = default;
  void operator()(T* ptr) const {delete ptr;}//using m_deleter with () overload and using it as deleter
};

#endif
