//
//
//

#ifndef ICSA_MEMORY_ALLOCATOR_HPP
#define ICSA_MEMORY_ALLOCATOR_HPP

#include "icsa/memory/memory_fwd.hpp"

#include "icsa/memory/propagation_traits.hpp"
// using icsa::memory::propagation_traits

#include "icsa/memory/allocation_traits.hpp"
// using icsa::memory::allocation_traits

#include <memory>
// using std::pointer_traits

#include <type_traits>
// using std::make_unsigned

#include <cstddef>
// using std::size_t

namespace icsa {
namespace memory {

template <typename T, typename Storage>
struct allocator {
  template <typename U, typename S>
  friend struct allocator;

  using allocation_traits = allocation_traits<Storage>;
  using ptr_traits = std::pointer_traits<T *>;
  using prop_traits = propagation_traits<Storage>;

  using value_type = T;
  using size_type =
      typename std::make_unsigned<typename ptr_traits::difference_type>::type;
  using pointer = typename ptr_traits::pointer;
  using storage_type = Storage;

  using propagate_on_container_copy_assignment =
      typename prop_traits::propagate_on_container_copy_assignment;
  using propagate_on_container_move_assignment =
      typename prop_traits::propagate_on_container_move_assignment;
  using propagate_on_container_swap =
      typename prop_traits::propagate_on_container_swap;

  allocator(Storage &s) noexcept : storage(s) {}

  allocator(const allocator &other) noexcept : storage(other.storage) {}

  template <typename U>
  allocator(allocator<U, Storage> &other) noexcept : storage(other.storage) {}

  allocator &operator=(const allocator &rhs) = delete;

  pointer allocate(size_type n, void * = 0) {
    return static_cast<pointer>(storage.allocate(n, alignof(T)));
  }

  void deallocate(pointer p, size_type n) noexcept { storage.deallocate(p, n); }

 protected:
  storage_type &storage;
};

// comparison between any two allocators

template <typename T, typename StorageT, typename U, typename StorageU>
bool operator==(const allocator<T, StorageT> &lhs,
                const allocator<U, StorageU> &rhs) {
  return false;
}

template <typename T, typename StorageT, typename U, typename StorageU>
bool operator!=(const allocator<T, StorageT> &lhs,
                const allocator<U, StorageU> &rhs) {
  return !(lhs == rhs);
}

// comparison between an allocator and anything else

template <typename T, typename StorageT, typename Other>
bool operator==(const allocator<T, StorageT> &lhs, const Other &rhs) {
  return false;
}

template <typename T, typename StorageT, typename Other>
bool operator!=(const allocator<T, StorageT> &lhs, const Other &rhs) {
  return !(lhs == rhs);
}

}  // namespace memory end
}  // namespace icsa end

#endif  // header
