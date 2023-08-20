#include "cat.hpp"

int main() {
    cat::async(cat::Priority::NORMAL, [](){
            cat::Window* win = cat::new_window({0,0},{20,20});
            win->box();
            win->draw_at({1,1},"Hello, World");
            win->redraw();

            win->set_key_handler([](const cat::key& k)->bool {
                return k >= '0' && k <= '9';
            },[=](const cat::key& k) {
                win->draw_at({1,2}, "%d", k - '0');
                win->redraw();
            });
    });

    cat::async(cat::Priority::HIGH, [](){
        cat::set_keymap('q', []() {
            cat::signals::quit = true;
        });

        cat::on_error([](){
            std::cerr << cat::signals::error;
            cat::signals::quit = true;
        });
    });

    cat::cycle();
}
