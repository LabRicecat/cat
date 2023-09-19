#include "../../inc/base/settings.hpp"

namespace cat {

Settings apply(const Settings& applied) {
    Settings cpy = std::move(current_settings);
    current_settings = applied;
    return cpy;
}

} // namespace cat
