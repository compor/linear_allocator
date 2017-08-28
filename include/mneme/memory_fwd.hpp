//
//
//

#ifndef MNEME_MEMORY_FWD_HPP
#define MNEME_MEMORY_FWD_HPP

#include <cstddef>
// using std::size_t

namespace mneme {

template <typename T>
struct allocation_traits;

template <typename T>
struct propagation_traits;

template <std::size_t N>
struct memory_arena;

template <typename T, typename Storage>
struct allocator;

template <std::size_t N>
struct private_memory_arena;

template <std::size_t N>
struct shared_memory_arena;

}  // namespace mneme end

#endif  // header
