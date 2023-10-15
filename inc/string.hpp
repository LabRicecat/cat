#ifndef CAT_STRING_HPP
#define CAT_STRING_HPP

#include <string>
#include <list>
#include <functional>
#include <stdexcept>
#include <ncurses.h>

#include "string_iterator.hpp"

namespace cat {

/* used to insert colors right into the string */ 
class CatString {
    struct event {
        using fn_type = std::function<void(CatString&,WINDOW*)>;
        
        event() { }
        event(const std::string& s)
        : s(s) { str = true; }
        event(const fn_type& fn)
        : fn(fn) { str = false; }
 
        std::string s = "";
        fn_type fn;
        bool str = true;

        ~event() { }
    };
    std::list<event> string_src;

public:
    using fn_type = event::fn_type;

    CatString() { }
    CatString(const std::string& s) {
        string_src.push_back(s);
    }
    CatString(const char* s) {
        string_src.push_back(std::string(s));
    }
    CatString(const event::fn_type& fn) {
        string_src.push_back(fn);
    }
    CatString(const std::list<event> src) {
        string_src = src;
    }


    CatString& push_back(const std::string& s);
    CatString& push_back(const event::fn_type& fn);

    CatString& push_front(const std::string& s);
    CatString& push_front(const event::fn_type& fn);

    event pop();

    bool empty() const;

    std::list<event>& entries();
    const std::list<event>& entries() const;

    size_t size() const;

    CatString& erase(size_t pos, size_t n = 1);

    CatString& operator+=(const std::string& s);
    CatString& operator+=(const event::fn_type& fn);
    CatString& operator+=(const char& c);
    CatString& operator+=(const CatString& s);
    CatString& operator+=(const char* s);

    CatString operator+(const std::string& s) const;
    CatString operator+(const event::fn_type& fn) const;
    CatString operator+(const CatString& s) const;
    CatString operator+(const char* s) const;

    CatString operator+(const char& c) const;

    char& operator[](size_t pos);

    // gets rid of the effects
    std::string to_string() const;

    CatStringIterator begin();
    ConstCatStringIterator begin() const;

    ConstCatStringIterator end() const;
    CatStringIterator end();

    friend CatString operator+(const std::string&, const CatString&);
    friend CatString operator+(const fn_type&, const CatString&);
};

CatString operator+(const std::string& s, const CatString& cs);
CatString operator+(const CatString::fn_type& fn, const CatString& cs);

} // namespace cat

#endif
