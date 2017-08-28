//
//
//

#ifndef MNEME_SHARED_MEMORY_ARENA_HPP
#define MNEME_SHARED_MEMORY_ARENA_HPP

#include "mneme/memory_fwd.hpp"

#include "mneme/detail/shared_memory_arena_impl.hpp"

#include <cstddef>
// using std::size_t

namespace mneme {

template <std::size_t N>
struct shared_memory_arena : public detail::shared_memory_arena_impl<N> {};

}  // namespace mneme end

#endif  // header
