#ifndef CAT_CONTAINER_HPP
#define CAT_CONTAINER_HPP

#include "window.hpp"
#include "positional.hpp"

namespace cat {

class Container : public Positional {
public:
    using apply_event = std::function<void(Window*)>;
protected:
    std::vector<Window*> windows;
    std::vector<apply_event> events;
public:
    Container(const Vector2& position, const Vector2& resolution) 
    : Positional(position, resolution) { }

    virtual Window* add(Window* window);
    virtual Window* pop(Window* window);

    virtual size_t entries() const;

    virtual std::vector<Window*>::iterator begin();
    virtual std::vector<Window*>::iterator end();
    virtual std::vector<Window*>::const_iterator begin() const;
    virtual std::vector<Window*>::const_iterator end() const;

    virtual Container& apply();
    virtual Container& on_apply(const apply_event& event);

    virtual Container& move(const Vector2& position) override;
    virtual Container& resize(const Vector2& resolution) override;

    virtual Window* operator[](size_t index);
    virtual Window* at(size_t index);
    virtual const Window* at(size_t index) const;

    virtual Window* front();
    virtual const Window* front() const;
    virtual Window* back();
    virtual const Window* back() const;

    virtual ~Container() { }
};

inline std::vector<Container*> container_pool;

template<typename TContainer = Container>
    requires ( std::is_base_of_v<Container,TContainer> )
inline TContainer* new_container(const Vector2& position, const Vector2& resolution) {
    TContainer* c = new TContainer(position, resolution);
    container_pool.push_back(c);
    return c;
}

void remove_container(const Container* container);
void clear_container_pool();

} // namespace cat

#endif 
