//
//
//

#ifndef ICSA_MEMORY_PRIVATE_MEMORY_ARENA_HPP
#define ICSA_MEMORY_PRIVATE_MEMORY_ARENA_HPP

#include "icsa/memory/detail/private_memory_arena_impl.hpp"

namespace icsa {
namespace memory {

template <std::size_t N>
using private_memory_arena = detail::private_memory_arena_impl<N>;

}  // namespace memory end
}  // namespace icsa end

#endif  // header
