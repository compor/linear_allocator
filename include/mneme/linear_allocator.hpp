//
//
//

#ifndef MNEME_LINEAR_ALLOCATOR_HPP
#define MNEME_LINEAR_ALLOCATOR_HPP

#include "mneme/memory_fwd.hpp"

#include "mneme/allocator.hpp"

#include "mneme/private_memory_arena.hpp"

#include "mneme/shared_memory_arena.hpp"

#include <cstddef>
// using std::size_t

namespace mneme {

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

}  // namespace mneme end

#endif  // header
