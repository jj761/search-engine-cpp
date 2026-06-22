#include "../src/tokenizer.h"
#include <iostream>

void print_tokens(const std::vector<std::string> &tokens)
{
    for (const auto &t : tokens)
    {
        std::cout << "[" << t << "] ";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Test 1: plain words, no trailing punctuation" << std::endl;
    print_tokens(tokenize("The Quick Brown Fox"));

    std::cout << "Test 2: hyphenated word (current behavior, before hyphen rule added)" << std::endl;
    print_tokens(tokenize("white-bear"));

    std::cout << "Test 3: multi-hyphen word" << std::endl;
    print_tokens(tokenize("by-and-by"));

    std::cout << "Test 4: apostrophe word (current behavior, before apostrophe rule added)" << std::endl;
    print_tokens(tokenize("don't"));

    std::cout << "Test 5: boundary apostrophe (quoted word)" << std::endl;
    print_tokens(tokenize("'Hello'"));

    std::cout << "Test 6: curly apostrophe (current behavior, before normalization added)" << std::endl;
    print_tokens(tokenize("don\u2019t"));

    std::cout << "Test 7: normalize_quotes on curly apostrophe" << std::endl;
    std::string normalized = normalize_quotes("don\u2019t");
    std::cout << "[" << normalized << "]" << std::endl;

    std::cout << "Test 8: numbers" << std::endl;
    print_tokens(tokenize("Chapter 12 costs $25 in 1865"));

    return 0;
}