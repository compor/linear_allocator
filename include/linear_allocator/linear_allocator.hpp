//
//
//

#ifndef LINEAR_ALLOCATOR_HPP
#define LINEAR_ALLOCATOR_HPP

#include <cstdlib>
// using std::malloc

#include <memory>
// using std::addressof

#include <new>
// using std::bad_alloc
// using ::operator new
// using std::nothrow

#include <cstddef>
// using std::ssize_t
// using std::ptrdiff_t

#include <type_traits>
// using std::true_type

#include <limits>
// using std::numeric_limits

#include <utility>
// using std:;forward

namespace icsa {

template <typename T>
class DefaultStorage {
 public:
  DefaultStorage() : m_ptr(nullptr) {}
  DefaultStorage(const DefaultStorage &other) = default;
  ~DefaultStorage() = default;

  T *get_storage(void) { return m_ptr; }

 protected:
  T *m_ptr;
};

template <typename T, typename Storage = DefaultStorage<T>>
class linear_allocator : public Storage {
  using at = std::allocator_traits<linear_allocator<T>>;

 public:
  using value_type = T;
  // using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using propagate_on_container_move_assignment = std::true_type;
  using is_always_equal = std::true_type;

  template <typename U>
  struct rebind {
    using other = linear_allocator<U>;
  };

  linear_allocator(const size_type s) noexcept : m_total_size(s) {
    typename at::pointer storage = Storage::get_storage();
    storage = static_cast<typename at::pointer>(std::malloc(m_total_size));
    return;
  };

  linear_allocator(const linear_allocator &other) noexcept = delete;

  ~linear_allocator() {
    typename at::pointer storage = Storage::get_storage();
    std::free(storage);
    return;
  }

  typename at::pointer address(reference x) const noexcept {
    return std::addressof(x);
  }

  const_pointer address(const_reference x) const noexcept {
    return std::addressof(x);
  }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  typename at::pointer allocate(size_type n, void * = 0) {
    if (n > max_size()) throw std::bad_alloc();

    return static_cast<typename at::pointer>(
        ::operator new(n * sizeof(value_type), std::nothrow));
  }

  // TODO determine if it has noexcept specification
  // no mention in cppreference.com, check standard
  void deallocate(typename at::pointer p, std::size_t n) noexcept {
    ::operator delete(static_cast<void *>(p));
    return;
  }

  template <typename U, typename... Ts>
  void construct(typename std::pointer_traits<U>::pointer p, Ts &&... args) {
    ::operator new(p, std::forward<Ts>(args)...);
    return;
  }

  template <typename U>
  void destroy(typename std::pointer_traits<U>::pointer p) {
    p->~U();
    return;
  }

 protected:
  const size_type m_total_size;

  template <typename U>
  linear_allocator(const linear_allocator<U> &other) noexcept {};
};

template <typename T1, typename T2>
bool operator==(const linear_allocator<T1> &lhs,
                const linear_allocator<T2> &rhs) {
  return true;
}

template <typename T1, typename T2>
bool operator!=(const linear_allocator<T1> &lhs,
                const linear_allocator<T2> &rhs) {
  return !(lhs == rhs);
}

}  // namespace icsa end

#endif  // header
