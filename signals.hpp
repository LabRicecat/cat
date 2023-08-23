#ifndef CAT_SIGNALS_HPP
#define CAT_SIGNALS_HPP

#include <string>
#include <functional>
#include <vector>
#include <cstdint>
#include <map>

namespace cat {

namespace signals {
    using signal = uint64_t;
    using tag_type = uint64_t;
    struct SignalData;
    using listener = std::function<void(const signal&, const SignalData*)>;
    using tag_listener = std::function<void(const tag_type&, const signal&, const SignalData*)>;
    
    static inline std::map<tag_type,std::vector<signal>> tags;
    static inline std::map<signal,std::vector<tag_type>> rtags_map;

    struct SignalData {
        virtual size_t id() const { return typeid(*this).hash_code(); }

        virtual ~SignalData() { } // no UB lol 
    };

    static inline std::vector<listener> listeners;
    static inline std::vector<tag_listener> tag_listeners;

    static inline signal tag(signal sig, tag_type tag) {
        tags[tag].push_back(sig);
        rtags_map[sig].push_back(tag);
        return sig;
    }

    static inline signal create() {
        static uint64_t sigc = 0;
        return sigc++;
    }

    static inline signal create(tag_type tag) {
        return cat::signals::tag(create(), tag);
    }

    static inline void listen(const listener& siglistener) {
        listeners.push_back(siglistener);
    }
    static inline void listen_tag(const tag_listener& taglistener) {
        tag_listeners.push_back(taglistener);
    }

    static inline void emit(signal sig, const SignalData* data = nullptr, bool clean = true) {
        for(auto& i : listeners)
            i(sig, data);
        for(auto& i : rtags_map[sig])
            for(auto& j : tag_listeners)
                j(sig, data);
        if(clean && data != nullptr)
            delete data;
    }

    static inline void emit_tag(tag_type tag, const SignalData* data = nullptr) {
        for(auto& i : tags[tag])
            emit(i, data, false);
        if(data != nullptr)
            delete data;
    }

    static inline tag_type new_tag() {
        static tag_type tagc = 0;
        return tagc++;
    }

    template<typename TData>
        requires ( std::is_base_of_v<SignalData,TData> )
    static inline auto id_of() {
        return TData().id();
    }

    static inline const tag_type error_tag = new_tag();
    static inline const signal quit_signal = create();

    struct MessageData : public SignalData {
        std::string msg;
        MessageData(const std::string& msg): msg(msg) { }
    };
}

static inline void error(const std::string& msg) {
    signals::emit_tag(signals::error_tag, new signals::MessageData(msg));    
}

}

#endif
