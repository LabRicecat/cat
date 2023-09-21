#include "../../inc/base/string_iterator.hpp"

namespace cat {

std::string::iterator CatStringIterator::next() {
    if(adv >= lst.size()) return lst.back()->end();
        
    ++current;
    if(current == lst[adv]->end()) {
        if(++adv >= lst.size()) return lst.back()->end();
        return current = lst[adv]->begin();
    }
        
    return current;
} 

CatStringIterator& CatStringIterator::operator++() {
    next();
    return *this;
}

char& CatStringIterator::operator*() {
    return *current;
}

CatStringIterator& CatStringIterator::set_end() { 
    current = lst.back()->end();
    return *this;
} 

bool CatStringIterator::operator==(const CatStringIterator& i) { return i.current == current; }
bool CatStringIterator::operator!=(const CatStringIterator& i) { return i.current != current; } 

CatStringIterator& CatStringIterator::operator+=(size_t n) {
    while(n-- > 0)
        next();
    return *this;
}
CatStringIterator CatStringIterator::operator+(size_t n) {
    CatStringIterator cp = *this;
    return cp += n;
}

std::string::const_iterator ConstCatStringIterator::next() {
    if(adv >= lst.size()) return lst.back()->cend();
        
    ++current;
    if(current == lst[adv]->cend()) {
        if(++adv >= lst.size()) return lst.back()->cend();
        return current = lst[adv]->cbegin();
    }
        
    return current;
} 

ConstCatStringIterator& ConstCatStringIterator::operator++() {
    next();
    return *this;
}

const char& ConstCatStringIterator::operator*() {
    return *current;
}
    
ConstCatStringIterator& ConstCatStringIterator::set_end() { 
    current = lst.back()->cend();
    return *this;
}
    
bool ConstCatStringIterator::operator==(const ConstCatStringIterator& i) { return i.current == current; }
bool ConstCatStringIterator::operator!=(const ConstCatStringIterator& i) { return i.current != current; }

ConstCatStringIterator& ConstCatStringIterator::operator+=(size_t n) {
    while(n-- > 0)
        next();
    return *this;
}
ConstCatStringIterator ConstCatStringIterator::operator+(size_t n) {
    ConstCatStringIterator cp = *this;
    return cp += n;
}

} // namespace cat
