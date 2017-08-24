//
//
//

#ifndef ICSA_MEMORY_ALLOCATION_TRAITS
#define ICSA_MEMORY_ALLOCATION_TRAITS

#include "icsa/memory/memory_fwd.hpp"

#include <cstddef>
// using std::size_t

#include <type_traits>
// using std::false_type

namespace icsa {
namespace memory {

template <typename T>
struct allocation_traits {
  using size_type = std::size_t;

  static void *allocate(T &s, size_type n, std::size_t a) {
    return s.allocate(n, a);
  }

  static void deallocate(T &s, void *p, size_type n) { s.deallocate(p, n); }
};

}  // namespace memory end
}  // namespace icsa end

#endif  // header
