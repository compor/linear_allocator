//
//
//

#ifndef ICSA_MEMORY_LINEAR_ALLOCATOR_HPP
#define ICSA_MEMORY_LINEAR_ALLOCATOR_HPP

#include "icsa/memory/memory_fwd.hpp"

#include "icsa/memory/propagation_traits.hpp"
// using icsa::memory::propagation_traits

#include "icsa/memory/allocation_traits.hpp"
// using icsa::memory::allocation_traits

#include <memory>
// using std::allocator_traits

#include <cstddef>
// using std::size_t

namespace icsa {
namespace memory {

template <typename T, typename Storage>
struct allocator : public Storage {
  using allocation_traits = allocation_traits<Storage>;
  using allocator_traits = std::allocator_traits<allocator>;
  using prop_traits = propagation_traits<Storage>;

  using value_type = T;

  using propagate_on_container_copy_assignment =
      typename prop_traits::propagate_on_container_copy_assignment;
  using propagate_on_container_move_assignment =
      typename prop_traits::propagate_on_container_move_assignment;
  using propagate_on_container_swap =
      typename prop_traits::propagate_on_container_swap;

  typename allocator_traits::pointer allocate(
      typename allocator_traits::size_type n, void * = 0) {
    return allocation_traits::allocate(n);
  }

  void deallocate(typename allocator_traits::pointer p,
                  typename allocator_traits::size_type n) noexcept {
    allocation_traits::deallocate(p, n);
  }
};

// comparison between any two allocators

template <typename T, typename StorageT, typename U, typename StorageU>
bool operator==(const allocator<T, StorageT> &lhs,
                const allocator<U StorageU> &rhs) {
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
bool operator!= =(const allocator<T, StorageT> &lhs, const Other &rhs) {
  return !(lhs == rhs);
}

}  // namespace memory end
}  // namespace icsa end

#endif  // header
