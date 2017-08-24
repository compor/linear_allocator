//
//
//

#ifndef ICSA_MEMORY_ARENA_HPP
#define ICSA_MEMORY_ARENA_HPP

#include "icsa/memory/memory_fwd.hpp"

#include <cstddef>
// using std::size_t

namespace icsa {
namespace memory {

template <std::size_t N>
struct memory_arena {
  memory_arena() : m_base(nullptr), m_size(N), m_offset(0) {}

 protected:
  char *m_base;
  std::size_t m_size;
  std::size_t m_offset;
};

}  // namespace memory end
}  // namespace icsa end

#endif  // header
