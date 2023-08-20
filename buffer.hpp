#ifndef CAT_BUFFER_HPP
#define CAT_BUFFER_HPP

#include <string>
#include <functional>

namespace cat {

class Window;

class Buffer {
public:
    using image_type = std::string;
    using snippet_type = std::string;
    using processor_type = std::function<image_type(const snippet_type&, Buffer*)>; // processes the snippet 
    using renderer_type = std::function<image_type(const image_type&, Buffer*)>; // makes the image fit the correct size

protected:
    std::string raw;
    Window* assoc_window = nullptr;

    std::vector<processor_type> processors;
    renderer_type renderer;

    virtual snippet_type generate_snippet() {
        return raw; // to implement by the derived classes 
    }
    
    virtual processor_type default_processor() {
        return [](const snippet_type& snippet, Buffer*) { return (image_type)snippet; };
    }

    virtual renderer_type default_renderer() {
        return [](const image_type& image, Buffer*) { return image; };
    }

public:

    Buffer() = delete;
    Buffer(Window* win): assoc_window(win) {
        processors = {default_processor()};
        renderer = default_renderer();
    }

    virtual Window* window() {
        return assoc_window;
    }

    virtual Buffer& set(const std::string& raw) {
        this->raw = raw;
        return *this;
    }
    virtual const std::string& get_raw() {
        return raw;
    }

    virtual image_type display() {
        image_type image = generate_snippet();
        for(auto& i : processors)
            image = i(image,this);

        return renderer(image,this);
    }
};

}

#endif
