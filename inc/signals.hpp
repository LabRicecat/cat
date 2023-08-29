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
        virtual size_t id() const;

        virtual ~SignalData() { } // no UB lol 
    };

    static inline std::vector<listener> listeners;
    static inline std::vector<tag_listener> tag_listeners;

    signal tag(signal sig, tag_type tag);

    signal create();
    signal create(tag_type tag);

    void listen(const listener& siglistener);
    void listen_tag(const tag_listener& taglistener);

    void emit(signal sig, const SignalData* data = nullptr, bool clean = true);
    void emit_tag(tag_type tag, const SignalData* data = nullptr);

    tag_type new_tag();

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
} // namespace signals

void error(const std::string& msg); 

} // namespace cat

#endif
