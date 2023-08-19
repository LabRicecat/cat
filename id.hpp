#ifndef CAT_ID_HPP
#define CAT_ID_HPP

#include <cstdint>

namespace cat {

using id_type = uint64_t;
static inline id_type id_increment = 0;

static inline id_type new_id() {
    return id_increment++;    
}

}

#endif
