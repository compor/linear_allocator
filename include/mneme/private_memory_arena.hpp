//
//
//

#ifndef MNEME_PRIVATE_MEMORY_ARENA_HPP
#define MNEME_PRIVATE_MEMORY_ARENA_HPP

#include "mneme/memory_fwd.hpp"

#include "mneme/detail/private_memory_arena_impl.hpp"

#include <cstddef>
// using std::size_t

namespace mneme {

template <std::size_t N>
struct private_memory_arena : public detail::private_memory_arena_impl<N> {};

}  // namespace mneme end

#endif  // header
