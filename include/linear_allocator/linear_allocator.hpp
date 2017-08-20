//
//
//

#ifndef ICSA_LINEAR_ALLOCATOR_HPP
#define ICSA_LINEAR_ALLOCATOR_HPP

#include "propagation_traits.hpp"
// using icsa::propagation_traits

#include "storage_traits.hpp"
// using icsa::storage_traits

#include <memory>
// using std::allocator_traits

#include <cstddef>
// using std::size_t

namespace icsa {

template <typename T, typename Storage>
class linear_allocator : public Storage {
  using alloc_traits = std::allocator_traits<linear_allocator>;
  using prop_traits = propagation_traits<Storage>;
  using storage_traits = storage_traits<Storage>;

 public:
  using value_type = T;

  using propagate_on_container_copy_assignment =
      prop_traits::propagate_on_container_copy_assignment;
  using propagate_on_container_move_assignment =
      prop_traits::propagate_on_container_move_assignment;
  using propagate_on_container_swap = prop_traits::propagate_on_container_swap;

  typename alloc_traits::pointer allocate(typename alloc_traits::size_type n,
                                          void* = 0) {
    return storage_traits::allocate(n);
  }

  void deallocate(typename alloc_traits::pointer p,
                  typename alloc_traits::size_type n) noexcept {
    storage_traits::deallocate(p, n);
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
