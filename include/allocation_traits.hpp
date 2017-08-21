//
//
//

#ifndef ICSA_ALLOCATION_TRAITS
#define ICSA_ALLOCATION_TRAITS

#include <cstddef>
// using std::size_t

#include <type_traits>
// using std::false_type

namespace icsa {

template <typename T>
struct allocation_traits {
  using size_type = std::size_t;

  static void *allocate(size_type n) { return nullptr; }
  static void allocate(void *p, size_type n) { return; }
};

}  // namespace icsa end

#endif  // header
