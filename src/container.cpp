#include "../inc/container.hpp"

namespace cat {

Window* Container::add(Window* window) {
    windows.push_back(window);
    return window;
}

Window* Container::pop(Window* window) {
    for(size_t i = 0; i < windows.size(); ++i)
        if(windows[i] == window)
            windows.erase(windows.begin() + (i--));
    return window;
}

size_t Container::entries() const {
    return windows.size();
}

std::vector<Window*>::iterator Container::begin() {
    return windows.begin();
}
std::vector<Window*>::iterator Container::end() {
    return windows.end();
}
std::vector<Window*>::const_iterator Container::begin() const {
    return windows.begin();
}
std::vector<Window*>::const_iterator Container::end() const {
    return windows.end();
}

Container& Container::apply() {
    for(auto& i : windows)
        for(auto& eve : events)
            eve(i);
    return *this;
}

Container& Container::on_apply(const Container::apply_event& event) {
    events.push_back(event);
    return *this;
}

Container& Container::move(const Vector2& position) {
    Positional::move(position);
    apply();
    return *this;
}

Container& Container::resize(const Vector2& resolution) {
    Positional::resize(resolution);
    apply();
    return *this;
}

Window* Container::operator[](size_t index) {
    return *(begin() + index);
}

Window* Container::at(size_t index) {
    if(index >= entries()) return nullptr;
    return *(begin() + index);
}
const Window* Container::at(size_t index) const {
    if(index >= entries()) return nullptr;
    return *(begin() + index);
}

Window* Container::front() {
    if(entries() == 0) return nullptr;
    return windows.front();
}
const Window* Container::front() const {
    if(entries() == 0) return nullptr;
    return windows.front();
}

Window* Container::back() {
    if(entries() == 0) return nullptr;
    return windows.back();
}
const Window* Container::back() const {
    if(entries() == 0) return nullptr;
    return windows.back();
}

void remove_container(const Container* container) {
    if(!container) return;
    for(size_t i = 0; i < container_pool.size(); ++i)
        if(container_pool[i] == container)
            container_pool.erase(container_pool.begin() + (i--));
}

void clear_container_pool() {
    for(auto& i : container_pool) {
        if(i) delete i;
        i = nullptr;
    }
    container_pool.clear();
}

} // namespace cat
