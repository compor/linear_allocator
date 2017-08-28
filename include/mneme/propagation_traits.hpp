//
//
//

#ifndef MNEME_PROPAGATION_TRAITS_HPP
#define MNEME_PROPAGATION_TRAITS_HPP

#include "mneme/memory_fwd.hpp"

#include <type_traits>
// using std::true_type
// using std::false_type

namespace mneme {

template <typename T>
struct propagation_traits {
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::false_type;
  using propagate_on_container_swap = std::false_type;
};

}  // namespace mneme end

#endif  // header
