#ifndef KMP_hpp
#define KMP_hpp

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace algorithm_space {
    class KMP {
        std::string text_string;
        std::string word;

        std::unique_ptr<std::size_t[]> partial_match_table;
        std::vector<std::size_t> matching;
        bool finished_matching;

        void generate_partial_match_table() {
            partial_match_table = std::make_unique<std::size_t[]>(word.length());
            std::size_t const word_length = word.length();
            std::size_t j = 0;

            for(std::size_t i = 1; i < word_length; i++) {
                while(j && word[i] != word[j]) {
                    j = partial_match_table[j - 1];
                }
                if(word[i] == word[j]) {
                    partial_match_table[i] = ++j;
                }
            }
        }

        void kmp() {
            if(finished_matching) return;

            std::size_t const text_length = text_string.length();
            std::size_t const word_length = word.length();
            std::size_t j = 0;

            for(std::size_t i = 0; i < text_length; i++) {
                while(j && text_string[i] != word[j]) {
                    j = partial_match_table[j - 1];
                }
                if(text_string[i] == word[j]) {
                    if(j == word_length - 1) {
                        matching.push_back(i - word_length + 1);
                        j = partial_match_table[j];
                    }
                    else j++;
                }
            }

            finished_matching = true;
        }

    public:
        KMP() = default;
        KMP(std::string text_string) : text_string(std::move(text_string)), finished_matching(false) {}
        KMP(std::string text_string, std::string word) : text_string(std::move(text_string)), word(std::move(word)), finished_matching(false) {
            generate_partial_match_table();
        }
        ~KMP() = default;

        [[nodiscard]] std::string_view get_text() const { return text_string; }
        [[nodiscard]] std::string_view get_word() const { return word; }

        void set_text(std::string txt) {
            text_string = std::move(txt);
            finished_matching = false;
        }
        void set_word(std::string wrd) {
            word = std::move(wrd);
            generate_partial_match_table();
            finished_matching = false;
        }

        [[nodiscard]] std::vector<std::size_t> const &get_matching() {
            kmp();
            return matching;
        }
    };
}

#endif