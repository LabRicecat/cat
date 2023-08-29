#ifndef CAT_STRING_ITERATOR_HPP
#define CAT_STRING_ITERATOR_HPP

#include <string>
#include <vector>

namespace cat {

struct CatStringIterator {
    std::vector<std::string*> lst;
    std::string::iterator current;
    size_t adv = 0;

    CatStringIterator(const std::vector<std::string*>& v) {
        lst = v;
        current = lst.front()->begin();
    }
    
    auto next() {
        if(adv >= lst.size()) return lst.back()->end();
        
        ++current;
        if(current == lst[adv]->end()) {
            if(++adv >= lst.size()) return lst.back()->end();
            return current = lst[adv]->begin();
        }
        
        return current;
    } 

    CatStringIterator& operator++() {
        next();
        return *this;
    }

    char& operator*() {
        return *current;
    }

    CatStringIterator& set_end() { 
        current = lst.back()->end();
        return *this;
    } 

    bool operator==(const CatStringIterator& i) 
    { return i.current == current; }
    bool operator!=(const CatStringIterator& i) 
    { return i.current != current; }
};

struct ConstCatStringIterator {
    std::vector<const std::string*> lst;
    std::string::const_iterator current;
    size_t adv = 0;

    ConstCatStringIterator(const std::vector<const std::string*>& v) {
        lst = v;
        current = lst.front()->cbegin();
    }

    auto next() {
        if(adv >= lst.size()) return lst.back()->cend();
        
        ++current;
        if(current == lst[adv]->cend()) {
            if(++adv >= lst.size()) return lst.back()->cend();
            return current = lst[adv]->cbegin();
        }
        
        return current;
    } 

    ConstCatStringIterator& operator++() {
        next();
        return *this;
    }

    const char& operator*() {
        return *current;
    }
    
    ConstCatStringIterator& set_end() { 
        current = lst.back()->cend();
        return *this;
    }
    
    bool operator==(const ConstCatStringIterator& i) 
    { return i.current == current; }
    bool operator!=(const ConstCatStringIterator& i) 
    { return i.current != current; }

};

}

#endif 
