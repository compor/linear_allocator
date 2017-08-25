//
//
//

#ifndef ICSA_MEMORY_LINEAR_ALLOCATOR_HPP
#define ICSA_MEMORY_LINEAR_ALLOCATOR_HPP

#include "icsa/memory/memory_fwd.hpp"

#include "icsa/memory/allocator.hpp"

#include "icsa/memory/private_memory_arena.hpp"

#include "icsa/memory/shared_memory_arena.hpp"

#include <cstddef>
// using std::size_t

namespace icsa {
namespace memory {

template <typename T, std::size_t N>
using linear_private_allocator = allocator<T, private_memory_arena<N>>;

template <typename T, typename U, std::size_t N>
bool operator==(const linear_private_allocator<T, N> &lhs,
                const linear_private_allocator<U, N> &rhs) {
  return false;
}

template <typename T, typename U, std::size_t N>
bool operator!=(const linear_private_allocator<T, N> &lhs,
                const linear_private_allocator<U, N> &rhs) {
  return !(lhs == rhs);
}

//

template <typename T, std::size_t N>
using linear_shared_allocator = allocator<T, shared_memory_arena<N>>;

template <typename T, typename U, std::size_t N>
bool operator==(const linear_shared_allocator<T, N> &lhs,
                const linear_shared_allocator<U, N> &rhs) {
  return false;
}

template <typename T, typename U, std::size_t N>
bool operator!=(const linear_shared_allocator<T, N> &lhs,
                const linear_shared_allocator<U, N> &rhs) {
  return !(lhs == rhs);
}

}  // namespace memory end
}  // namespace icsa end

#endif  // header
