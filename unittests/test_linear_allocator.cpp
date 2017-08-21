//
//
//

#include "gtest/gtest.h"
// using testing::Test

namespace {

class test_linear_allocator : public testing::Test {
 public:
  test_linear_allocator() {}

 protected:
};

TEST_F(test_linear_allocator, foo) {
  //icsa::linear_allocator<int> lalloc(100);

  //int *t = lalloc.allocate(1);
  //*t = 10;
  //lalloc.deallocate(t, 1);

  EXPECT_TRUE(true);
}
}  // namespace anonymous end
