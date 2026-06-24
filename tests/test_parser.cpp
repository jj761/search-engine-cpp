#include <iostream>
#include "../src/parser.h"

void print_result(const ParsedQuery &pq)
{
    std::cout << "type: " << (pq.type == QueryType::PHRASE ? "PHRASE" : "KEYWORD")
              << "  term: \"" << pq.term << "\"\n";
}

int main()
{
    // Test 1: normal keyword query
    std::cout << "=== Test 1: keyword query ===\n";
    print_result(parse_query("white whale"));

    // Test 2: phrase query with double quotes
    std::cout << "=== Test 2: phrase query ===\n";
    print_result(parse_query("\"white whale\""));

    // Test 3: leading and trailing whitespace stripped
    std::cout << "=== Test 3: whitespace trimming ===\n";
    print_result(parse_query("   white whale   "));

    // Test 4: quoted query with inner whitespace preserved
    std::cout << "=== Test 4: phrase with inner whitespace ===\n";
    print_result(parse_query("\"  white whale  \""));

    // Test 5: single word keyword
    std::cout << "=== Test 5: single word ===\n";
    print_result(parse_query("whale"));

    // Test 6: single word phrase
    std::cout << "=== Test 6: single word phrase ===\n";
    print_result(parse_query("\"whale\""));

    // Test 7: lone quote — must not be detected as phrase
    std::cout << "=== Test 7: lone quote ===\n";
    print_result(parse_query("\""));

    // Test 8: empty string
    std::cout << "=== Test 8: empty string ===\n";
    print_result(parse_query(""));

    return 0;
}