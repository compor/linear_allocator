//
//
//

#ifndef ICSA_MEMORY_PRIVATE_MEMORY_ARENA_HPP
#define ICSA_MEMORY_PRIVATE_MEMORY_ARENA_HPP

#include "icsa/memory/memory_fwd.hpp"

#include "icsa/memory/detail/private_memory_arena_impl.hpp"

#include <cstddef>
// using std::size_t

namespace icsa {
namespace memory {

template <std::size_t N>
struct private_memory_arena : public detail::private_memory_arena_impl<N> {};

}  // namespace memory end
}  // namespace icsa end

#endif  // header
