#include "cat.hpp"

class MyBuffer : public cat::LockableBuffer, public cat::ScrollBuffer {
public:
    MyBuffer(cat::Window* win)
        : cat::LockableBuffer(win), cat::ScrollBuffer(win), cat::Buffer(win) { }
};

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

    cat::async(cat::Priority::NORMAL, [](){
        cat::Window* win2 = cat::new_window({30,0},{10,5});
        win2->box();

        cat::Composer custom_composer = [](const cat::Composer::param_type& param, const cat::Buffer*) { 
            return param + param;         
        };

        win2->set_buffer<MyBuffer>(
                cat::renderers::fit_hight & cat::renderers::fit_width, 
                custom_composer
            );

        win2->on_redraw([](cat::Window* win2){
            win2->get_buffer<MyBuffer>()->set("Hello, World!\n");
            win2->draw_buffer({1,1}); // offset of 1,1 because of box()
        });

        win2->redraw();
    });

    cat::async(cat::Priority::NORMAL, [](){
        cat::Window* input_window = cat::new_window<cat::InputFieldWindow>({30,20},{10,10});
        input_window->draw(input_window->has_module<cat::InputFieldWindow>() ? "true" : "false");
        input_window->set_buffer<cat::Buffer>();
        input_window->get_buffer()->composer() &= cat::composers::line_numbers;
        input_window->redraw();
    });

    cat::async(cat::Priority::HIGH, [](){
        cat::set_keymap('q', []() {
            cat::signals::emit(cat::signals::quit_signal);
        });

        cat::signals::listen_tag([](const cat::signals::tag_type& tag, const cat::signals::signal& signal, const cat::signals::SignalData* data) {
            if(tag == cat::signals::error_tag)
                std::cerr << "Error";
        });
    });

    cat::cycle();
}
