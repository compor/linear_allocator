#ifndef ICSA_ALLOCATION_TRAITS
#define ICSA_ALLOCATION_TRAITS

#include <cstddef>
// using std::size_t

#include <type_traits>
// using std::false_type

#include <pointer_traits>
// using std::pointer_traits

namespace icsa {

template <typename T>
struct allocation_traits {
  using pointer = std::pointer_traits<T>::pointer;
  using size_type = std::size_t;

  static pointer allocate(size_type n) { return nullptr; }
  static void allocate(pointer p, size_type n) { return; }
};

}  // namespace icsa end

#endif  // header
