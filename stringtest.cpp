#include <cat/base/string.hpp>

#include <iostream>

int main() {
    using namespace cat;
    CatString s = "Hello World";
    std::cout << s.insert(3,"WEE").to_string() << "\n";

}
