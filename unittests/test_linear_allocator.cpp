//
//
//

#include "gtest/gtest.h"
// using testing::Test

#include <iostream>
// using std::cout

#include "icsa/memory/linear_allocator.hpp"

namespace imem = icsa::memory;

namespace {

class test_linear_allocator : public testing::Test {
 public:
  test_linear_allocator() {}

 protected:
};

TEST_F(test_linear_allocator, foo) {
  using alloc_t = int;
  using lpa_t = icsa::memory::linear_private_allocator<alloc_t, 100>;
  lpa_t::storage_type s;

  lpa_t lpa{s};

  std::vector<alloc_t, lpa_t> v{lpa};

  v.push_back(1);
  v.push_back(99);
  v.push_back(5);
  v.push_back(32);

  for (const auto &e : v) std::cout << e << std::endl;

  EXPECT_TRUE(true);
}
}  // namespace anonymous end
