//
//
//

#include <iostream>

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

#include <cstdint>
// using std::uintptr_t

#include "icsa/memory/linear_allocator.hpp"

namespace imem = icsa::memory;

namespace {

class test_linear_shared_allocator : public testing::Test {
 public:
  test_linear_shared_allocator() {}

 protected:
};

// basic usage of allocator

// vector<T> currently uses an allocator to allocate nodes of sizeof(T)

TEST_F(test_linear_shared_allocator, vector_allocation_basic) {
  using alloc_t = int;

  std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  using lpa_t = imem::linear_private_allocator<alloc_t, 150>;

  lpa_t::storage_type s;
  lpa_t lpa{s};
  std::vector<alloc_t, lpa_t> dst{lpa};

  for (const auto &e : src) dst.push_back(e);

  EXPECT_TRUE(std::equal(src.begin(), src.end(), dst.begin()));
}

// list<T> currently uses an allocator to allocate nodes of
// sizeof(list::node<T>)

TEST_F(test_linear_shared_allocator, list_allocation_basic) {
  using alloc_t = int;

  std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  using lpa_t = imem::linear_private_allocator<alloc_t, 450>;

  lpa_t::storage_type s;
  lpa_t lpa{s};
  std::list<alloc_t, lpa_t> dst{lpa};

  for (const auto &e : src) dst.push_back(e);

  EXPECT_TRUE(std::equal(src.begin(), src.end(), dst.begin()));
}

// check proper alignment from allocator usage when storage is manually
// misaligned with initial allocation of less strict type than the one used in
// the container

TEST_F(test_linear_shared_allocator, vector_allocation_misalignment) {
  using alloc_t = int;

  std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  using lpa_t = imem::linear_private_allocator<alloc_t, 450>;

  lpa_t::storage_type s;

  auto *sptr =
      imem::allocation_traits<decltype(s)>::allocate(s, 1, alignof(char));
  auto *ptr = reinterpret_cast<char *>(sptr) + 1;
  auto ptrval = reinterpret_cast<std::uintptr_t>(ptr);
  auto mod1 = ptrval % alignof(alloc_t);

  lpa_t lpa{s};
  std::vector<alloc_t, lpa_t> dst{lpa};

  for (const auto &e : src) dst.push_back(e);

  auto *p2 = std::addressof(dst[0]);
  auto ptrval2 = reinterpret_cast<std::uintptr_t>(p2);
  auto mod2 = ptrval2 % alignof(alloc_t);

  imem::allocation_traits<decltype(s)>::deallocate(s, sptr, 1);

  EXPECT_TRUE(mod1 && !mod2);
}

// use of different allocator objects but of same type and using the same
// underlying storage

TEST_F(test_linear_shared_allocator,
       vector_allocation_different_allocator_objects_same_storage) {
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

// use of different allocator objects but of same type and using the same
// underlying storage during a container copy

TEST_F(test_linear_shared_allocator,
       vector_allocation_different_allocator_objects_during_copy) {
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

// use of different allocator objects but of same type and using the same
// underlying storage during a container move

TEST_F(test_linear_shared_allocator,
       vector_allocation_different_allocator_objects_during_move) {
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

  dst1 = std::move(dst2);

  auto cmp1 = std::equal(src.rbegin(), src.rend(), dst1.begin());

  EXPECT_TRUE(cmp1);
}

// use of different allocator objects of different type and using the same
// underlying storage during a container move

// clang-format off
//TEST_F(
    //test_linear_shared_allocator,
    //vector_allocation_different_allocator_objects_different_type_during_move) {
  //using alloc_t = int;

  //std::array<int, 9> src{3, 99, 1001, 5, 32, 973, 973, 32, 5};

  //using lpa1_t = imem::linear_private_allocator<alloc_t, 300>;
  //using lpa2_t = imem::linear_private_allocator<alloc_t, 400>;

  //lpa1_t::storage_type s1;
  //lpa1_t lpa1{s1};
  //lpa2_t::storage_type s2;
  //lpa2_t lpa2{s2};
  //std::vector<alloc_t, lpa1_t> dst1{lpa1};
  //std::vector<alloc_t, lpa2_t> dst2{lpa2};

  //for (const auto &e : src) dst1.push_back(e);

  //for (auto it = src.rbegin(), ei = src.rend(); it != ei; ++it)
    //dst2.push_back(*it);

  //dst1 = std::move(dst2);

  //auto cmp1 = std::equal(src.rbegin(), src.rend(), dst1.begin());

  //EXPECT_TRUE(cmp1);
//}
// clang-format on

}  // namespace anonymous end
