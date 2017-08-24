//
//
//

#include "gtest/gtest.h"
// using testing::Test

#include <array>
// using std::array

#include <vector>
// using std::vector

#include <list>
// using std::list

#include <algorithm>
// using std::equal

#include "icsa/memory/linear_allocator.hpp"

namespace imem = icsa::memory;

namespace {

class test_linear_allocator : public testing::Test {
 public:
  test_linear_allocator() {}

 protected:
};

TEST_F(test_linear_allocator, vector_allocation) {
  using alloc_t = int;

  std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  using lpa_t = imem::linear_private_allocator<alloc_t, 150>;

  lpa_t::storage_type s;
  lpa_t lpa{s};
  std::vector<alloc_t, lpa_t> dst{lpa};

  for (const auto &e : src) dst.push_back(e);

  EXPECT_TRUE(std::equal(src.begin(), src.end(), dst.begin()));
}

TEST_F(test_linear_allocator, list_allocation) {
  using alloc_t = int;

  std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  using lpa_t = imem::linear_private_allocator<alloc_t, 450>;

  lpa_t::storage_type s;
  lpa_t lpa{s};
  std::list<alloc_t, lpa_t> dst{lpa};

  for (const auto &e : src) dst.push_back(e);

  EXPECT_TRUE(std::equal(src.begin(), src.end(), dst.begin()));
}

}  // namespace anonymous end
