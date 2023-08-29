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


    CatString& push_back(const std::string& s) {
        string_src.push_back(s);
        return *this;
    }
    CatString& push_back(const event::fn_type& fn) {
        string_src.push_back(fn);
        return *this;
    }

    CatString& push_front(const std::string& s) {
        string_src.push_front(s);
        return *this;
    }
    CatString& push_front(const event::fn_type& fn) {
        string_src.push_front(fn);
        return *this;
    }

    event pop() {
        event last = string_src.back();
        string_src.pop_back();
        return last;
    }

    bool empty() const {
        return string_src.empty();
    }

    std::list<event>& entries() {
        return string_src;
    }
    const std::list<event>& entries() const {
        return string_src;
    }

    size_t size() const {
        size_t s = 0;
        for(auto& i : string_src)
            if(i.str) s+= i.s.size();
        return s;
    }

    CatString& erase(size_t pos, size_t n = 1) {
        if(n == 0) return *this;
        if(pos >= size()) throw std::out_of_range("pos >= size()");
        
        size_t p = 0;
        for(auto& i : string_src) {
            if(i.str) {
                for(size_t c = 0; c < i.s.size(); ++c) {
                    if(p == pos && n != 0) {
                        if(n > i.s.size()-c) {
                            n -= i.s.size()-c;
                            i.s.erase(c,i.s.size()-c);
                            c = i.s.size();
                        }
                        else {
                            i.s.erase(i.s.begin()+c, i.s.begin()+c+n);
                            n = 0;
                        }
                    }
                    else ++p;
                }
            }
        }
            
        return *this;
    }

    CatString& operator+=(const std::string& s) { return push_back(s); }
    CatString& operator+=(const event::fn_type& fn) { return push_back(fn); }
    CatString& operator+=(const char& c) { return push_back(std::string(1,c)); }
    CatString& operator+=(const CatString& s) {
        for(auto& i : s.string_src)
            string_src.push_back(i);
        return *this;
    }
    CatString& operator+=(const char* s) { return push_back(s); }

    CatString operator+(const std::string& s) const {
        return CatString(this->string_src).push_back(s);
    }
    CatString operator+(const event::fn_type& fn) const {
        return CatString(this->string_src).push_back(fn);
    }
    CatString operator+(const CatString& s) const {
        CatString f = *this;
        for(auto& i : s.string_src)
            f.string_src.push_back(i);
        return f;
    }
    CatString operator+(const char* s) const {
        return CatString(*this).push_back(s);
    }

    CatString operator+(const char& c) const {
        return CatString(*this).push_back(std::string(1,c));
    }

    char& operator[](size_t pos) {
        size_t p = 0;
        for(auto& i : string_src)
            if(i.str) {
                for(auto& j : i.s)
                    if(p == pos) return j;
                    else ++p;
            }
        throw std::out_of_range("pos > size()");
    }

    // gets rid of the colors 
    std::string to_string() const {
        std::string r;
        for(auto& i : string_src)
            if(i.str) r += i.s;
        return r;
    }

    CatStringIterator begin() {
        std::vector<std::string*> s;
        for(auto& i : string_src)
            if(i.str) s.push_back(&i.s);

        return s;
    }
    ConstCatStringIterator begin() const {
        std::vector<const std::string*> s;
        for(auto& i : string_src)
            if(i.str) s.push_back(&i.s);

        return s;
    }
    ConstCatStringIterator end() const {
        return begin().set_end();
    }
    CatStringIterator end() {
        return begin().set_end();
    }

    friend CatString operator+(const std::string&, const CatString&);
    friend CatString operator+(const fn_type&, const CatString&);
};

inline CatString operator+(const std::string& s, const CatString& cs) {
    return CatString(s) += cs;
}

inline CatString operator+(const CatString::fn_type& fn, const CatString& cs) {
    return CatString(fn) += cs;
}

}

#endif
