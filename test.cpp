#include <cat/cat.hpp>
#include <cat/signals.hpp>

int main() {
    cat::lib::InputField* my_win;

    cat::async(cat::Priority::NORMAL, [&]() {
        my_win = cat::new_window<cat::lib::InputField>({0,0}, {20,20});

        cat::set_keymap(cat::shift('c'), []() {
            cat::signals::emit(
                    cat::signals::quit_signal
                );
        });
    });

    cat::cycle({ .color = false, .stuck_cursor = true });
}
