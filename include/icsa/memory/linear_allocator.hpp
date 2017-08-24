//
//
//

#ifndef ICSA_MEMORY_LINEAR_ALLOCATOR_HPP
#define ICSA_MEMORY_LINEAR_ALLOCATOR_HPP

#include "icsa/memory/memory_fwd.hpp"

#include "icsa/memory/allocator.hpp"

#include "icsa/memory/private_memory_arena.hpp"

#include <cstddef>
// using std::size_t

namespace icsa {
namespace memory {

template <typename T, std::size_t N>
using linear_private_allocator = allocator<T, private_memory_arena<N>>;

template <typename T, typename U, std::size_t NT, std::size_t NU>
bool operator==(const linear_private_allocator<T, NT> &lhs,
                const linear_private_allocator<U, NU> &rhs) {
  return true;
}

template <typename T, typename U, std::size_t NT, std::size_t NU>
bool operator!=(const linear_private_allocator<T, NT> &lhs,
                const linear_private_allocator<U, NU> &rhs) {
  return !(lhs == rhs);
}

}  // namespace memory end
}  // namespace icsa end

#endif  // header
