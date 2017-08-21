//
//
//

#ifndef ICSA_LINEAR_ALLOCATOR_HPP
#define ICSA_LINEAR_ALLOCATOR_HPP

#include "propagation_traits.hpp"
// using icsa::propagation_traits

#include "allocation_traits.hpp"
// using icsa::allocation_traits

#include <memory>
// using std::allocator_traits

#include <cstddef>
// using std::size_t

namespace icsa {

template <typename T, typename Storage>
struct linear_allocator : public Storage {
  using allocator_traits = std::allocator_traits<linear_allocator>;
  using prop_traits = propagation_traits<Storage>;
  using allocation_traits = allocation_traits<Storage>;

  using value_type = T;

  using propagate_on_container_copy_assignment =
      prop_traits::propagate_on_container_copy_assignment;
  using propagate_on_container_move_assignment =
      prop_traits::propagate_on_container_move_assignment;
  using propagate_on_container_swap = prop_traits::propagate_on_container_swap;

  typename allocator_traits::pointer allocate(
      typename allocator_traits::size_type n, void* = 0) {
    return allocation_traits::allocate(n);
  }

  void deallocate(typename allocator_traits::pointer p,
                  typename allocator_traits::size_type n) noexcept {
    allocation_traits::deallocate(p, n);
  }
};

// template <typename T1, typename T2>
// bool operator==(const linear_allocator<T1> &lhs,
// const linear_allocator<T2> &rhs) {
// return true;
//}

// template <typename T1, typename T2>
// bool operator!=(const linear_allocator<T1> &lhs,
// const linear_allocator<T2> &rhs) {
// return !(lhs == rhs);
//}

}  // namespace icsa end

#endif  // header
