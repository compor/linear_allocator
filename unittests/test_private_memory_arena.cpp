//
//
//

#include "linear_allocator/private_memory_arena.hpp"

#include <cstdlib>
// using std::exit

#include <csignal>
// using SIGSEGV

#include "gtest/gtest.h"
// using testing::Test

namespace {

class test_private_memory_arena : public testing::Test {
 public:
  test_private_memory_arena() {}

  template <typename T>
  void access(T *ptr) {
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

TEST_F(test_private_memory_arena, zero_allocation_segfault) {
  icsa::private_memory_arena<0> pma;
  using alloc_t = int;

  auto *p1 = pma.allocate(sizeof(alloc_t), alignof(alloc_t));
  auto *p2 = reinterpret_cast<alloc_t *>(p1);

  EXPECT_EXIT(access(p2), ::testing::KilledBySignal(SIGSEGV), ".*");
}

TEST_F(test_private_memory_arena, allocation_segfault) {
  icsa::private_memory_arena<1> pma;
  using alloc_t = int;
  static_assert(sizeof(alloc_t) > 1, "sizeof int must be larger than 1");

  auto *p1 = pma.allocate(sizeof(alloc_t), alignof(int));
  auto *p2 = reinterpret_cast<alloc_t *>(p1);

  EXPECT_EXIT(access(p2), ::testing::KilledBySignal(SIGSEGV), ".*");
}

}  // namespace anonymous end
