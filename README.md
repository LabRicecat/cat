# cat 0.2.0
Cat Approved TUI - a TUI framework, meow~

## Requirements
- C++ 20
- cmake 
- make 
- ncurses 

## Installation
```sh
$ git clone https://github.com/LabRicecat/cat
$ cd cat
$ mkdir build && cd build
$ cmake ..
$ sudo make install
```

## Usage
For details read the **[documentation](https://labricecat.github.io/docs/cat/)**.
### Example
This is an example from `examples/example.cpp`

```cpp
#include <cat/cat.hpp> // include the framework

int main() {
        // execute some code next frame once 
    cat::async(cat::Priority::NORMAL, []() {
            // creates a new window at 0,0 with the resolution 30x10 
        cat::Window* my_window = cat::new_window({0,0},{30,10});
            // draws some text to the window 
        my_window->draw("Hello, World!");
            
            // mark this window to be redrawn next frame
        my_window->redraw();
        
            // set a window key event 
        my_window->set_key('o', [=]() {
                // clears the screen
                // It's adviced to avoid this function to avoid lag
            my_window->clear(); 
                // draws a c formatted string in the color red 
            my_window->draw(cat::effect::red + "Oh a %s event!", "key"); 
                // redraw ...
            my_window->redraw();
        });
    });
        // execute some code next frame once, with higher priority
    cat::async(cat::Priority::HIGH, []() {
            // set a global key event
        cat::set_keymap('q', []() {
                // emit to the framework to shut down
            cat::signals::emit(
                    cat::signals::quit_signal
                );
        });
    });
        
        // start the framework with some settings 
    cat::cycle(cat::Settings{ .color = true, });
}
```
