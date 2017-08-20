#ifndef ICSA_MEMORY_ARENA
#define ICSA_MEMORY_ARENA

#include <cstddef>
// using std::size_t

#include <memory>
// using std::pointer_traits

namespace icsa {

template <std::size_t N>
struct memory_arena {
  memory_arena() : m_base(nullptr), m_size(N), m_offset(0) {}

 protected:
  char *m_base;
  std::size_t m_size;
  std::size_t m_offset;
};

}  // namespace icsa end

#endif  // header
