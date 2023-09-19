#include "../../inc/base/id.hpp"

namespace cat {

id_type new_id() {
    return id_increment++;    
}

} // namespace cat
