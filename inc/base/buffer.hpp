#ifndef CAT_BUFFER_HPP
#define CAT_BUFFER_HPP

#include <string>
#include <functional>

#include "string.hpp"

namespace cat {

class Buffer;
using image_type = CatString;
using snippet_type = CatString;

template<typename Tcomp>
inline Tcomp compose(const Tcomp& r0) {
    return r0;
}

template<typename Tcomp, typename... TcompP>
inline Tcomp compose(const Tcomp& r0, const Tcomp& r1, const TcompP& ...tail) {
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
    CatString raw;
    Window* assoc_window = nullptr;

    Composer i_composer = [](const Composer::param_type& data, Buffer*) { return (Composer::return_type)data; };
    Renderer i_renderer = [](const Renderer::param_type& data, Buffer*) { return (Renderer::return_type)data; };

    virtual snippet_type generate_snippet(); 
public:

    Buffer() = delete;
    Buffer(Window* win): assoc_window(win) { }

    virtual Window* window();

    virtual Buffer& set(const std::string& raw);
    virtual Buffer& append(const std::string& raw);
    virtual CatString& get_raw();

    virtual Buffer& clear();

    virtual Composer& composer();
    virtual Renderer& renderer();

    virtual image_type display();

    virtual ~Buffer() { }

    friend class Window;
};

} // namespace cat

#endif
