#ifndef CAT_LIFESPAN_HPP
#define CAT_LIFESPAN_HPP

#include <functional>
#include <vector>
#include <map>
#include <thread>
#include <chrono>

#include "drawing.hpp"
#include "signals.hpp"
#include "config.hpp"

namespace cat {

enum class Priority {
    HIGH,
    NORMAL,
    LOW
};

using process = std::function<void()>;
using process_queue = std::vector<process>; 

static inline std::map<Priority,process_queue> processes;
static inline std::map<Priority,process_queue> async_processes;

static inline void pass_input(int input) {
    if(input == ERR) return; // no input
    
    if(in_global_keymap(input)) {
        global_keymap[input]();
        return;
    }
    
    Window* focused = get_focused();
    if(focused) {
        if(focused->do_key_check(input)) {
            focused->get_key_handler()(input);
            return;
        }
        if(focused->has_key(input)) {
            focused->get_key_event(input)();
            return;
        }
    }

    Window* next_handle = next_handler(input);
    if(next_handle) {
        if(next_handle->do_key_check(input)) 
            next_handle->get_key_handler()(input);
        else next_handle->get_key_event(input)();
    }
}

static inline void update() {
    for(auto& [_,queue] : async_processes)
        for(auto& job : queue)
            job();

    for(auto& [_,queue] : processes)
        for(auto& job : queue)
            job(); 
    
    async_processes.clear();
}

static inline void cycle() {
    init();
    config::sync();
    refresh();
    
    bool running = true;

    signals::listen([&](const signals::signal& sig, const signals::SignalData*) { 
        if(sig == signals::quit_signal)
            running = false;
    });

    while(running) {
        pass_input(getch());
        
        update();
        redraw();

        int frame_sleep = config::get_or<int>("frame_sleep", "CAT_TUI", 50);
        std::this_thread::sleep_for(std::chrono::milliseconds(frame_sleep));
    }

    config::apply();
    exit();
}

static inline void queue_process(const Priority& priority, const process& process) {
    processes[priority].push_back(process);
}

static inline void async(const Priority& priority, const process& process) {
    async_processes[priority].push_back(process);
}

}

#endif
