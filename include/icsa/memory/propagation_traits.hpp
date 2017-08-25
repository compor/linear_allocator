//
//
//

#ifndef ICSA_MEMORY_PROPAGATION_TRAITS_HPP
#define ICSA_MEMORY_PROPAGATION_TRAITS_HPP

#include "icsa/memory/memory_fwd.hpp"

#include <type_traits>
// using std::true_type
// using std::false_type

namespace icsa {
namespace memory {

template <typename T>
struct propagation_traits {
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::false_type;
  using propagate_on_container_swap = std::false_type;
};

}  // namespace memory end
}  // namespace icsa end

#endif  // header
