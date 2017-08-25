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

#include <memory>
// using std::addressof

#include "icsa/memory/linear_allocator.hpp"

namespace imem = icsa::memory;

namespace {

class test_linear_allocator : public testing::Test {
 public:
  test_linear_allocator() {}

 protected:
};

TEST_F(test_linear_allocator, vector_allocation_use) {
  using alloc_t = int;

  std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  using lpa_t = imem::linear_private_allocator<alloc_t, 150>;

  lpa_t::storage_type s;
  lpa_t lpa{s};
  std::vector<alloc_t, lpa_t> dst{lpa};

  for (const auto &e : src) dst.push_back(e);

  EXPECT_TRUE(std::equal(src.begin(), src.end(), dst.begin()));
}

TEST_F(test_linear_allocator, list_allocation_use) {
  using alloc_t = int;

  std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  using lpa_t = imem::linear_private_allocator<alloc_t, 450>;

  lpa_t::storage_type s;
  lpa_t lpa{s};
  std::list<alloc_t, lpa_t> dst{lpa};

  for (const auto &e : src) dst.push_back(e);

  EXPECT_TRUE(std::equal(src.begin(), src.end(), dst.begin()));
}

TEST_F(test_linear_allocator,
       vector_allocation_use_different_allocators_same_storage) {
  using alloc_t = int;

  std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  using lpa_t = imem::linear_private_allocator<alloc_t, 300>;

  lpa_t::storage_type s;
  lpa_t lpa{s};
  std::vector<alloc_t, lpa_t> dst1{lpa};
  std::vector<alloc_t, lpa_t> dst2{lpa};

  for (const auto &e : src) dst1.push_back(e);
  for (const auto &e : src) dst2.push_back(e);

  auto cmp1 = std::equal(src.begin(), src.end(), dst1.begin());
  auto cmp2 = std::equal(src.begin(), src.end(), dst2.begin());
  auto cmp3 = std::equal(src.begin(), src.end(), dst2.begin(), dst2.end(),
                         [](const auto &e1, const auto &e2) {
                           return std::addressof(e1) != std::addressof(e2);
                         });

  EXPECT_TRUE(cmp1 && cmp2 && cmp3);
}

TEST_F(test_linear_allocator,
       vector_allocation_use_different_allocators_during_copy) {
  using alloc_t = int;

  std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  using lpa_t = imem::linear_private_allocator<alloc_t, 300>;

  lpa_t::storage_type s;
  lpa_t lpa1{s};
  lpa_t lpa2{s};
  std::vector<alloc_t, lpa_t> dst1{lpa1};
  std::vector<alloc_t, lpa_t> dst2{lpa2};

  for (const auto &e : src) dst1.push_back(e);

  for (auto it = src.rbegin(), ei = src.rend(); it != ei; ++it)
    dst2.push_back(*it);

  dst1 = dst2;

  auto cmp1 = std::equal(src.rbegin(), src.rend(), dst1.begin());
  auto cmp2 = std::equal(dst1.begin(), dst1.end(), dst2.begin());

  EXPECT_TRUE(cmp1 && cmp2);
}

TEST_F(test_linear_allocator,
       vector_allocation_use_different_allocators_during_move) {
  using alloc_t = int;

  std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  using lpa_t = imem::linear_private_allocator<alloc_t, 800>;

  lpa_t::storage_type s;
  lpa_t lpa1{s};
  lpa_t lpa2{s};
  std::vector<alloc_t, lpa_t> dst1{lpa1};
  std::vector<alloc_t, lpa_t> dst2{lpa2};

  for (const auto &e : src) dst1.push_back(e);

  for (auto it = src.rbegin(), ei = src.rend(); it != ei; ++it)
    dst2.push_back(*it);

  dst1 = std::move(dst2);

  auto cmp1 = std::equal(src.rbegin(), src.rend(), dst1.begin());

  EXPECT_TRUE(cmp1);
}

}  // namespace anonymous end
