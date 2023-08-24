#ifndef CAT_BUFFER_HPP
#define CAT_BUFFER_HPP

#include <string>
#include <functional>

namespace cat {

class Buffer;
using image_type = std::string;
using snippet_type = std::string;

template<typename Tcomp>
static inline Tcomp compose(const Tcomp& r0) {
    return r0;
}

template<typename Tcomp, typename... TcompP>
static inline Tcomp compose(const Tcomp& r0, const Tcomp& r1, const TcompP& ...tail) {
    return
        [=](const typename Tcomp::param_type& image, Buffer* buffer)
            ->typename Tcomp::return_type 
        { return r0(compose<Tcomp>(r1,tail...)(image, buffer), buffer); };
}


template<typename Treturn_type, typename Tparam_type>
struct Processor {
    using return_type = Treturn_type;
    using param_type = Tparam_type;
    using fn_type = std::function<return_type(const param_type&, Buffer*)>;

    fn_type fn;

    return_type operator()(const param_type& data, Buffer* buffer) { return fn(data, buffer); }
    return_type operator()(const param_type& data, Buffer* buffer) const { return fn(data, buffer); }


    template<typename Fn>
        requires ( !std::is_same_v<std::remove_cvref_t<Fn>,Processor> )
    Processor(Fn&& fn): fn(std::forward<Fn>(fn)) { }
    
    Processor(const fn_type& fn): fn(fn) { }
    Processor(fn_type&& fn): fn(fn) { }
    Processor() { }
    Processor& operator=(const Processor&) = default;
    
    Processor operator&(const Processor& processor) {
        return compose(*this, processor);
    }
    Processor& operator&=(const Processor& processor) {
        return *this = operator&(processor);
    }

    template<typename Fn>
        requires ( !std::is_same_v<std::remove_cvref_t<Fn>,Processor> )
    Processor& operator=(Fn&& fn) { 
        this->fn = std::forward<Fn>(fn);
        return *this;
    }

    Processor& operator=(const fn_type& fn) {
        this->fn = fn;
        return *this;
    }

    const static Processor null; 
}; 

template<typename T, typename U>
inline const Processor<T,U> Processor<T,U>::null = [](const Processor::param_type& param, Buffer*) { return (Processor::return_type)param; };

using Renderer = Processor<image_type,image_type>;
using Composer = Processor<image_type,snippet_type>;

class Window;

class Buffer {
protected:
    std::string raw;
    Window* assoc_window = nullptr;

    Composer i_composer = [](const Composer::param_type& data, Buffer*) { return (Composer::return_type)data; };
    Renderer i_renderer = [](const Renderer::param_type& data, Buffer*) { return (Renderer::return_type)data; };

    virtual snippet_type generate_snippet() {
        return raw; // to implement by the derived classes 
    }
public:

    Buffer() = delete;
    Buffer(Window* win): assoc_window(win) { }

    virtual Window* window() {
        return assoc_window;
    }

    virtual Buffer& set(const std::string& raw) {
        this->raw = raw;
        return *this;
    }
    virtual Buffer& append(const std::string& raw) {
        this->raw += raw;
        return *this;
    }
    virtual std::string& get_raw() {
        return raw;
    }

    virtual Buffer& clear() {
        raw = "";
        return *this;
    }

    virtual Composer& composer() { return i_composer; }
    virtual Renderer& renderer() { return i_renderer; }

    virtual image_type display() {
        return i_renderer(
            i_composer(
                generate_snippet(),
            this),
        this);
    }

    virtual ~Buffer() { }

    friend class Window;
};

}

#endif
