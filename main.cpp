#include <iostream>
#include <string>
#include <string_view>

#include "KMP.hpp"

using algorithm_space::KMP;

int main() {
    std::string text, word;
    std::cin >> text >> word;
    
    KMP kmp(text, word);
    auto const &matching = kmp.get_matching();
    for(auto i : matching) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}