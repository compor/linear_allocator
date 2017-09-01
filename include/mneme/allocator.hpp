//
//
//

#ifndef MNEME_ALLOCATOR_HPP
#define MNEME_ALLOCATOR_HPP

#include "mneme/memory_fwd.hpp"

#include "mneme/propagation_traits.hpp"
// using mneme::propagation_traits

#include "mneme/allocation_traits.hpp"
// using mneme::allocation_traits

#include <memory>
// using std::pointer_traits

#include <type_traits>
// using std::make_unsigned
// using std::true_type
// using std::false_type

#if __GNUC__ < 6
#include <utility>
// using std::forward
#endif  // __GNUC__ < 6

#include <cstddef>
// using std::size_t

namespace mneme {

template <typename T, typename Storage>
struct allocator {
  template <typename U, typename S>
  friend struct allocator;

  using allocation_traits = mneme::allocation_traits<Storage>;
  using pointer_t = T *;
  using pointer_traits = std::pointer_traits<pointer_t>;
  using propagation_traits = mneme::propagation_traits<Storage>;

  using value_type = T;

  // these are required because they are used in later definitions for which we
  // do not rely on std::allocator_traits defaults
  using pointer = typename pointer_traits::pointer;
  using size_type = typename std::make_unsigned<
      typename pointer_traits::difference_type>::type;

#if __GNUC__ < 6
  using const_pointer =
      typename pointer_traits::template rebind<const value_type>;
  using reference = T &;
  using const_reference = const T &;

  template <typename U>
  struct rebind {
    typedef allocator<U, Storage> other;
  };
#endif  // __GNUC__ < 6

  using storage_type = Storage;

  using propagate_on_container_copy_assignment =
      typename propagation_traits::propagate_on_container_copy_assignment;
  using propagate_on_container_move_assignment =
      typename propagation_traits::propagate_on_container_move_assignment;
  using propagate_on_container_swap =
      typename propagation_traits::propagate_on_container_swap;

  allocator(Storage &s) noexcept : storage(s) {}

  allocator(const allocator &other) noexcept : storage(other.storage) {}

  template <typename U>
  allocator(const allocator<U, Storage> &other) noexcept
      : storage(other.storage) {}

  // TODO maybe we can provide this using a reference wrapper
  allocator &operator=(const allocator &rhs) = delete;

  pointer allocate(size_type n, void * = 0) {
    return static_cast<pointer>(
        allocation_traits::allocate(storage, n * sizeof(T), alignof(T)));
  }

  void deallocate(pointer p, size_type n) noexcept {
    allocation_traits::deallocate(storage, p, n);
  }

#if __GNUC__ < 6
  template <typename U, typename... Args>
  void construct(U *p, Args &&... args) {
    ::new (static_cast<void *>(p)) U(std::forward<Args>(args)...);
  }

  template <typename U>
  void destroy(U *p) {
    p->~U();
  }
#endif  // __GNUC__ < 6

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

}  // namespace mneme end

#endif  // header
