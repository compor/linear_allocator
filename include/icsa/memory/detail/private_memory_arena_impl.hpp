//
//
//

#ifndef ICSA_MEMORY_PRIVATE_MEMORY_ARENA_IMPL_HPP
#define ICSA_MEMORY_PRIVATE_MEMORY_ARENA_IMPL_HPP

#include "icsa/memory/memory_arena.hpp"

#include <cstddef>
// using std::size_t

#include <new>
// using std::bad_alloc

#include <memory>
// using std::align

#include <sys/mman.h>
// using mmap
// using munmap

namespace icsa {
namespace memory {

namespace detail {

template <std::size_t N>
struct private_memory_arena_impl : public memory_arena<N> {
  using memory_arena<N>::m_base;
  using memory_arena<N>::m_size;
  using memory_arena<N>::m_offset;

  private_memory_arena_impl() {
    static_assert(N > 0, "allocation size must be greater than 0!");

    void *ptr = mmap(NULL, N, PROT_READ | PROT_WRITE,
                     MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (ptr == MAP_FAILED) throw std::bad_alloc();

    m_base = reinterpret_cast<decltype(m_base)>(ptr);
  }

  private_memory_arena_impl(const private_memory_arena_impl &) = delete;
  private_memory_arena_impl &operator=(const private_memory_arena_impl &) =
      delete;

  ~private_memory_arena_impl() { munmap(m_base, m_size); }

  void *allocate(std::size_t n, std::size_t a) {
    if (m_offset + n > m_size) return nullptr;

    void *ptr = m_base + m_offset;
    auto space = m_size - m_offset;
    auto modified_space = space;

    auto *rptr = std::align(a, n, ptr, modified_space);

    if (rptr) {
      auto added = space - modified_space + n;
      m_offset += added;
    }

    return rptr;
  }

  void deallocate(void *ptr, std::size_t) {}
};

}  // namespace detail end

}  // namespace memory end
}  // namespace icsa end

#endif  // header