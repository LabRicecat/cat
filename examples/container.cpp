#include <cat/cat.hpp>

/* displays usage of the `cat::HorizontalContainer` */

int main() {
        // creating our container
    cat::HorizontalContainer* container;
        
    // initializing with max hight/width
    cat::async(cat::Priority::NORMAL, [&]() {
        container = cat::new_container<cat::HorizontalContainer>({0,0},{cat::terminal::get_x(), cat::terminal::get_y()});
    });
        
        // define behaviour when applying 
        // changes to the container
    cat::async(cat::Priority::NORMAL, [&]() {
        container->on_apply([](cat::Window* win) {
            win->box();
            win->draw_buffer({1,1});
            win->redraw();
        });
    });
        
        // set a few key events
    cat::async(cat::Priority::HIGH, [&]() {
        cat::set_keymap('q', []() {
                // emit to the framework to shut down
            cat::signals::emit(
                    cat::signals::quit_signal
                );
        });
            
        cat::set_keymap({
                // create a new window 
            {'a', [&]() {
                cat::Window* win = container->add(cat::new_window());
                win->set_buffer();
                    // let the window display it's number
                win->get_buffer()->set(std::to_string(container->entries()));
                    
                    // if we are focused, take the cursor
                win->on_focus([](cat::Window* win, bool mode) {
                    if(mode) {
                        win->cursor({1,1});
                        win->redraw();
                    }
                });
                    
                    // apply changes
                container->apply();
                    
                    // if we are the first window, take focus
                if(container->entries() == 1)
                    win->focus();
            }},
                // remove last added window
            {'r', [&]() {
                    // remove only if there are windows left
                if(container->entries() != 0)
                    container->pop(container->back());

                container->apply();
            }},
                // refresh
            {'e', [&]() {
                container->apply();
            }}
        });
            
            // make it posible to switch between windows 
            // using the arrow keys
        cat::set_keymap(KEY_RIGHT, [&]() {
            for(size_t i = 0; i < container->entries(); ++i) {
                if(container->at(i)->focused()) {
                    if(i+1 == container->entries()) break;
                        
                        // move the focus one to the left
                    container->at(i)->lose_focus();
                    container->at(i+1)->focus();
                    break;
                }
            }
        });
        cat::set_keymap(KEY_LEFT, [&]() {
            for(size_t i = 0; i < container->entries(); ++i) {
                if(container->at(i)->focused()) {
                    if(i == 0) break;
                        
                        // move the focus one to the right
                    container->at(i)->lose_focus();
                    container->at(i-1)->focus();
                    break;
                }
            }
        });
    });
    
        // apply some settings
    cat::cycle({ .tick_sleep = 10, .color = false, .stuck_cursor = true });
}
