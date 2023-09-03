#ifndef CAT_LIBRARY_CONTAINER_HPP
#define CAT_LIBRARY_CONTAINER_HPP 

#include "../container.hpp"

namespace cat {

namespace lib {

class HorizontalContainer : public Container {
public:
    using Container::Container;

    virtual Container& apply() override;

};

} // namespace lib

} // namespace cat

#endif
