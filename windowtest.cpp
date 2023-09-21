#include <cat/cat.hpp> 


int main() {
    cat::TextField* field;

    cat::async(cat::Priority::NORMAL, [&]() {
        field = cat::new_window<cat::TextField>({0,0},{10,10});
        field->set_buffer<cat::Buffer>();
    });

    cat::async(cat::Priority::HIGH, [&]() {
        cat::set_keymap(cat::shift('q'), []() {
            cat::emit(cat::signals::quit_signal);
        });
    });
    
    cat::cycle({ .color = false });
}
