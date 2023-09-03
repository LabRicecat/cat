#include <cat/cat.hpp>

/* displayes usage of the framework to create a little shell */
/* STILL UNDER CONSTRUCTION !!! */

// define our own buffer for scroll behaviour
class DownFocusBuffer : public cat::Buffer {
    virtual cat::snippet_type generate_snippet() override {
        size_t visible = 0, lines = 1;
        for(auto& i : raw) {
            if(i == '\n')
                lines++;
            visible++;

            if(lines > window()->get_resolution().y)
                break;
        }

        return raw.substr(raw.size()-visible);
    }

public:
    using cat::Buffer::Buffer;

    DownFocusBuffer& remove(size_t pos) {
        raw.erase(raw.begin()+pos);
        return *this;
    }
    virtual DownFocusBuffer& append(size_t pos, const std::string& s) {
        raw.insert(pos, s);
        return *this;
    }

    std::string current_line() {
        std::string line;
        for(int i = raw.size()-1; i != -1; --i)
            if(raw[i] == '\n') break;
            else line = raw[i] + line;
        
        return line;
    }
};

// define our shell window class
class ShellWindow : public cat::Window {
    std::string layout = "[shell]>";
    size_t line_position = layout.size();
public:
    ShellWindow(const cat::Vector2& position, const cat::Vector2& resolution)
    : Window(position, resolution) {
        set_buffer<DownFocusBuffer>();
        get_buffer()->set(layout);
        set_key_handler([](const cat::key& k) { return isascii(k) || k == KEY_ENTER || k == KEY_BACKSPACE || k == KEY_LEFT || k == KEY_RIGHT; }, [&](const cat::key& k) {
            if(k == KEY_ENTER) {
                line_position = 0;
                handle(get_buffer<DownFocusBuffer>()->current_line());
                get_buffer()->append("\n" + layout);
            }
            else if(k == KEY_BACKSPACE) {
                if(line_position != layout.size()) {
                    this->clear();
                    get_buffer<DownFocusBuffer>()->remove(line_position - 1);
                    --line_position;
                }
            }
            else if(k == KEY_LEFT) {
                if(line_position != layout.size())
                    --line_position;
            }
            else if(k == KEY_RIGHT) {
                if(line_position != get_buffer<DownFocusBuffer>()->current_line().size())
                    ++line_position;
            }
            else if(isprint(k)) {
                this->get_buffer<DownFocusBuffer>()->append(line_position,std::string(1,(char)k));
                ++line_position;
            }
            
            cat::move_cursor(this, {(cat::Vector2::value_type)line_position, 0});
            draw_buffer();
            redraw();
        });

        cat::move_cursor(this, {(cat::Vector2::value_type)line_position, 0});
        draw_buffer();
        redraw();
    }

    void handle(const std::string& inp) {
        // ... do something with the input ...
    }
};

int main() {
    using namespace cat;
    async(Priority::NORMAL, []() {
        auto shell = new_window<ShellWindow>({0,0},{50,20});
        shell->redraw();

        set_keymap(shift('C'),[](){
            signals::emit(signals::quit_signal);
        });
    });

    cycle({ .stuck_cursor = true });
}
