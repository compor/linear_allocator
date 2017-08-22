//
//
//

#ifndef ICSA_MEMORY_MEMORY_FWD_HPP
#define ICSA_MEMORY_MEMORY_FWD_HPP

#include <cstddef>
// using std::size_t

namespace icsa {
namespace memory {

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

}  // namespace memory end
}  // namespace icsa end

#endif  // header
