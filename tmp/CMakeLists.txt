cmake_minimum_required(VERSION 3.14)
project(huffman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
add_executable(huffman lib/encoder.h lib/decoder.h lib/encoder.cpp lib/decoder.cpp test/test.h utility/file_work.h utility/freader.h utility/fwriter.h utility/file_work.cpp utility/freader.cpp utility/fwriter.cpp main.cpp test/test.cpp)