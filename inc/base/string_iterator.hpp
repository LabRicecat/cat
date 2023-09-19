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
    
    std::string::iterator next();

    CatStringIterator& operator++();
    char& operator*();

    CatStringIterator& set_end();

    bool operator==(const CatStringIterator& i);
    bool operator!=(const CatStringIterator& i); 
};

struct ConstCatStringIterator {
    std::vector<const std::string*> lst;
    std::string::const_iterator current;
    size_t adv = 0;

    ConstCatStringIterator(const std::vector<const std::string*>& v) {
        lst = v;
        current = lst.front()->cbegin();
    }

    std::string::const_iterator next();

    ConstCatStringIterator& operator++();
    const char& operator*();
    
    ConstCatStringIterator& set_end();
    
    bool operator==(const ConstCatStringIterator& i);
    bool operator!=(const ConstCatStringIterator& i); 

};

}

#endif 
