cmake_minimum_required(VERSION 3.16)

project(SearchEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(search_engine src/main.cpp src/loader.cpp src/tokenizer.cpp)
add_executable(test_corpus_tokenize tests/test_corpus_tokenize.cpp src/loader.cpp src/tokenizer.cpp)
