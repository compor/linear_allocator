//
//
//

#include "linear_allocator/private_memory_arena.hpp"

#include <cstdlib>
// using std::exit

#include <new>
// using std::bad_alloc

#include <csignal>
// using SIGSEGV

#include "gtest/gtest.h"
// using testing::Test

#include <iostream>

namespace {

class test_private_memory_arena : public testing::Test {
 public:
  test_private_memory_arena() {}

  template <typename T>
  void access(T *ptr) {
    *ptr = 9876;
    auto k = *ptr;
    std::exit(0);
  }
};

TEST_F(test_private_memory_arena, exact_size_allocation) {
  using alloc_t = int;
  icsa::private_memory_arena<sizeof(alloc_t)> pma;

  auto *p1 = pma.allocate(sizeof(alloc_t), alignof(alloc_t));
  auto *p2 = reinterpret_cast<alloc_t *>(p1);

  EXPECT_EXIT(access(p2), ::testing::ExitedWithCode(0), ".*");
}

TEST_F(test_private_memory_arena, allocation_segfault) {
  icsa::private_memory_arena<1> pma;
  using alloc_t = int;
  static_assert(sizeof(alloc_t) > 1, "sizeof int must be larger than 1");

  auto *p1 = pma.allocate(sizeof(alloc_t), alignof(alloc_t));
  auto *p2 = reinterpret_cast<alloc_t *>(p1);

  EXPECT_EXIT(access(p2), ::testing::KilledBySignal(SIGSEGV), ".*");
}

TEST_F(test_private_memory_arena, multiple_allocation_segfault) {
  using alloc_t = int;
  const std::size_t elements_number = 10;
  const std::size_t n = elements_number * sizeof(alloc_t);
  std::cerr << n << std::endl;
  icsa::private_memory_arena<n> pma;

  auto *p1 = pma.allocate(n, alignof(alloc_t));
  std::cerr << p1 << std::endl;
  auto *p2 = reinterpret_cast<alloc_t *>(p1);

  p2 += elements_number + 10000000;
  std::cerr << p2 << std::endl;

  EXPECT_EXIT(access(p2), ::testing::ExitedWithCode(0), ".*");
}

}  // namespace anonymous end
