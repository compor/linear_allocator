//
//
//

#include "gtest/gtest.h"
// using testing::Test

#include <cstdlib>
// using std::exit

#include <new>
// using std::bad_alloc

#include <array>
// using std::array

#include <algorithm>
// using std::copy
// using std::equal

#include <csignal>
// using SIGSEGV

#include "icsa/memory/private_memory_arena.hpp"

namespace imem = icsa::memory;

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
  imem::private_memory_arena<sizeof(alloc_t)> pma;

  auto *p1 = pma.allocate(sizeof(alloc_t), alignof(alloc_t));
  auto *p2 = reinterpret_cast<alloc_t *>(p1);

  EXPECT_EXIT(access(p2), ::testing::ExitedWithCode(0), ".*");
}

TEST_F(test_private_memory_arena, allocation_segfault) {
  imem::private_memory_arena<1> pma;
  using alloc_t = int;
  static_assert(sizeof(alloc_t) > 1, "sizeof int must be larger than 1");

  auto *p1 = pma.allocate(sizeof(alloc_t), alignof(alloc_t));
  auto *p2 = reinterpret_cast<alloc_t *>(p1);

  EXPECT_EXIT(access(p2), ::testing::KilledBySignal(SIGSEGV), ".*");
}

TEST_F(test_private_memory_arena, multiple_allocation) {
  using alloc_t = int;
  const std::size_t elements_number = 5;
  const std::size_t n = elements_number * sizeof(alloc_t);
  imem::private_memory_arena<n> pma;

  std::array<int, n> a{9987, 221, 872, 34, 67};

  auto *p1 = pma.allocate(n, alignof(alloc_t));
  auto *p2 = reinterpret_cast<alloc_t *>(p1);

  std::copy(a.begin(), a.end(), p2);

  EXPECT_TRUE(std::equal(a.begin(), a.end(), p2));
}

}  // namespace anonymous end
