#ifndef CAT_BUFFER_HPP
#define CAT_BUFFER_HPP

#include <string>
#include <functional>

namespace cat {

class Window;

class Buffer {
protected:
    std::string raw;
    Window* assoc_window = nullptr;

    using image_type = std::string;
    using snippet_type = std::string;
    using processor_type = std::function<image_type(const snippet_type&)>; // processes the snippet 
    using renderer_type = std::function<image_type(const image_type&)>; // makes the image fit the correct size

    processor_type processor;
    renderer_type renderer;

    virtual snippet_type generate_snippet() {
        return raw; // to implement by the derived classes 
    }
    
    virtual processor_type default_processor() {
        return [](const snippet_type& snippet) { return (image_type)snippet; };
    }

    virtual renderer_type default_renderer() {
        return [](const image_type& image) { return image; };
    }

public:

    Buffer() = delete;
    Buffer(Window* win): assoc_window(win) {
        processor = default_processor();
        renderer = default_renderer();
    }

    virtual Buffer& set(const std::string& raw) {
        this->raw = raw;
        return *this;
    }
    virtual const std::string& get_raw() {
        return raw;
    }

    virtual image_type display() {
        return renderer(
            processor(
                this->generate_snippet()
            )
        );
    }
};

}

#endif
