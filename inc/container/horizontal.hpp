#ifndef CAT_CONTAINER_HORIZONTAL_HPP
#define CAT_CONTAINER_HORIZONTAL_HPP 

#include "../base/container.hpp"

namespace cat {

class HorizontalContainer : public Container {
public:
    using Container::Container;

    virtual Container& apply() override;
};

} // namespace cat

#endif
