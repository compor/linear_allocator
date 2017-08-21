//
//
//

#ifndef ICSA_PROPAGATION_TRAITS
#define ICSA_PROPAGATION_TRAITS

#include <type_traits>
// using std::false_type

namespace icsa {

template <typename T>
struct propagation_traits {
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::false_type;
  using propagate_on_container_swap = std::false_type;
};

}  // namespace icsa end

#endif  // header
