//
//
//

#include "linear_allocator/private_memory_arena.hpp"

#include <cassert>
// using assert

#include <csignal>

#include "gtest/gtest.h"
// using testing::Test

namespace {

class test_private_memory_arena : public testing::Test {
 public:
  test_private_memory_arena() {}

 protected:
};

TEST_F(test_private_memory_arena, zero_allocation_segfault) {
  const std::size_t n = 0;
  icsa::private_memory_arena<n> pma;

  auto *raw = pma.allocate(sizeof(int), alignof(int));
  auto *ptr = reinterpret_cast<int *>(raw);

  EXPECT_EXIT({ int k = *ptr; }, ::testing::KilledBySignal(SIGSEGV), ".*");
}

TEST_F(test_private_memory_arena, allocation_segfault) {
  const std::size_t n = 1;
  icsa::private_memory_arena<n> pma;

  auto *raw = pma.allocate(sizeof(int), alignof(int));
  auto *ptr = reinterpret_cast<int *>(raw);

  EXPECT_EXIT({ int k = *ptr; }, ::testing::KilledBySignal(SIGSEGV), ".*");
}

}  // namespace anonymous end
