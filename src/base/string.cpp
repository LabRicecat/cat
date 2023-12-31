#include "../../inc/base/string.hpp"

namespace cat {

CatString& CatString::push_back(const CatString& s) {
    for(auto& i : s.string_src)
        string_src.push_back(i);
    return *this;
}

CatString& CatString::push_front(const CatString& s) {
    for(auto& i : s.string_src)
        string_src.push_front(i);
    return *this;
}

CatString::event CatString::pop() {
    event last = string_src.back();
    string_src.pop_back();
    return last;
}

bool CatString::empty() const {
    return string_src.empty();
}

std::list<CatString::event>& CatString::entries() {
    return string_src;
}
    
const std::list<CatString::event>& CatString::entries() const {
    return string_src;
}

size_t CatString::size() const {
    size_t s = 0;
    for(auto& i : string_src)
        if(i.str) s+= i.s.size();
    return s;
}

size_t CatString::length() const {
    return size();
}

CatString& CatString::erase(size_t pos, size_t n) {
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

// TODO
CatString& CatString::insert(size_t pos, const CatString& s) {
    for(auto i = string_src.begin(); i != string_src.end(); ++i)
        if(i->str) {
            if(i->s.size() < pos) {
                pos -= i->s.size();
            }
            else {
                if(pos != 0) {
                    std::string a = i->s.substr(0,pos);
                    std::string b = i->s.substr(pos);
                    string_src.erase(i--);
                    string_src.insert(i, a);
                    string_src.insert(i, b);
                }
                auto rbeg = s.string_src.rbegin();
                while(rbeg != s.string_src.rend()) {
                    string_src.insert(i, *rbeg);
                    ++rbeg;
                }
                break;
            }
        }

    return *this;
}

CatString& CatString::insert(size_t pos, char c) {
    size_t p = 0;
    for(auto& i : string_src)
        if(i.str) {
            if(i.s.size() + p < pos) p += i.s.size();
            else i.s.insert(i.s.begin() + pos - p, c);
        }

    return *this;
}

CatString& CatString::append(const CatString& c) {
    return push_back(c);
}

CatString CatString::substr(size_t pos) {
    CatString r;
    for(auto& i : string_src) {
        if(!i.str) r.push_back(i.fn);

        if(pos >= i.s.size()) pos -= i.s.size();
        else {
            r.push_back(i.s.substr(pos));
            pos = 0;
            break;
        }
    } 
    return r;
}

CatString CatString::substr(size_t pos, size_t n) {
    CatString cut = substr(pos);
    if(n == -1) return cut;

    CatString r;
    for(auto& i : cut.string_src) {
        if(!i.str) r.push_back(i.fn);
        else {
            if(n >= i.s.size()) {
                r.push_back(i.s);
                n -= i.s.size();
            }
            else {
                r.push_back(i.s.substr(0,n));
                n = 0;
                break;
            }
        }
    }
    return r; 
}

CatString& CatString::operator+=(const std::string& s) { return push_back(s); }
CatString& CatString::operator+=(const event::fn_type& fn) { return push_back(fn); }
CatString& CatString::operator+=(const char& c) { return push_back(std::string(1,c)); }
CatString& CatString::operator+=(const CatString& s) {
    for(auto& i : s.string_src)
         string_src.push_back(i);
    return *this;
}
CatString& CatString::operator+=(const char* s) { return push_back(s); }

CatString CatString::operator+(const std::string& s) const {
        return CatString(this->string_src).push_back(s);
}
CatString CatString::operator+(const CatString::event::fn_type& fn) const {
    return CatString(this->string_src).push_back(fn);
}
CatString CatString::operator+(const CatString& s) const {
    CatString f = *this;
    for(auto& i : s.string_src)
        f.string_src.push_back(i);
    return f;
}
CatString CatString::operator+(const char* s) const {
    return CatString(*this).push_back(s);
}

CatString CatString::operator+(const char& c) const {
    return CatString(*this).push_back(std::string(1,c));
}

char& CatString::operator[](size_t pos) {
    size_t p = 0;
    for(auto& i : string_src)
        if(i.str) {
            for(auto& j : i.s)
                if(p == pos) return j;
                else ++p;
        }
    throw std::out_of_range("pos > size()");
}

// gets rid of the effects 
 std::string CatString::to_string() const {
    std::string r;
    for(auto& i : string_src)
        if(i.str) r += i.s;
    return r;
}

CatStringIterator CatString::begin() {
    std::vector<std::string*> s;
    for(auto& i : string_src)
        if(i.str) s.push_back(&i.s);

    return s;
}

ConstCatStringIterator CatString::begin() const {
    std::vector<const std::string*> s;
    for(auto& i : string_src)
        if(i.str) s.push_back(&i.s);

    return s;
}

ConstCatStringIterator CatString::end() const {
    return begin().set_end();
}

CatStringIterator CatString::end() {
    return begin().set_end();
}

CatString operator+(const std::string& s, const CatString& cs) {
    return CatString(s) += cs;
}

CatString operator+(const CatString::fn_type& fn, const CatString& cs) {
    return CatString(fn) += cs;
}

} // namespace cat
