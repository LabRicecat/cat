#include "../../inc/base/signals.hpp"

namespace cat {

namespace signals {

size_t SignalData::id() const { return typeid(*this).hash_code(); }


signal tag(signal sig, tag_type tag) {
    tags[tag].push_back(sig);
    rtags_map[sig].push_back(tag);
    return sig;
}

signal create() {
    static uint64_t sigc = 0;
    return sigc++;
}

signal create(tag_type tag) {
    return cat::signals::tag(create(), tag);
}

void listen(const listener& siglistener) {
    listeners.push_back(siglistener);
}
    
void listen_tag(const tag_listener& taglistener) {
    tag_listeners.push_back(taglistener);
}

void emit(signal sig, const SignalData* data, bool clean) {
    for(auto& i : listeners)
        i(sig, data);
    for(auto& i : rtags_map[sig])
        for(auto& j : tag_listeners)
            j(sig, i, data);
    if(clean && data != nullptr)
        delete data;
}

void emit_tag(tag_type tag, const SignalData* data) {
    for(auto& i : tags[tag])
        emit(i, data, false);
    if(data != nullptr)
        delete data;
}

tag_type new_tag() {
    static tag_type tagc = 0;
    return tagc++;
}

} // namespace signals

void error(const std::string& msg) {
    signals::emit_tag(signals::error_tag, new signals::MessageData(msg));    
}

} // namespace cat
