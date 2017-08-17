//
//
//

#include "linear_allocator/linear_allocator.hpp"
#include "linear_allocator/allocator_traits.hpp"

#include <cassert>
// using assert

#include "gtest/gtest.h"
// using testing::Test

namespace {

class test_linear_allocator : public testing::Test {
 public:
  test_linear_allocator() {}

 protected:
};

TEST_F(test_linear_allocator, foo) { EXPECT_TRUE(true); }

}  // namespace anonymous end
