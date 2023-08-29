#include "../inc/lifespan.hpp"

namespace cat {

void pass_input(int input) {
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

void update() {
    for(auto& [_,queue] : async_processes)
        for(auto& job : queue)
            job();

    for(auto& [_,queue] : processes)
        for(auto& job : queue)
            job(); 
    
    async_processes.clear();
}

void cycle() {
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

void queue_process(const Priority& priority, const process& process) {
    processes[priority].push_back(process);
}

void async(const Priority& priority, const process& process) {
    async_processes[priority].push_back(process);
}

}
