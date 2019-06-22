//
// Created by pokerstar on 15.06.19.
//

#ifndef HUFFMAN_FREADER_H
#define HUFFMAN_FREADER_H
#include <vector>
#include <cstdio>

struct freader {
    freader(char const *name, char const *md);
    freader(freader const&) = delete;
    ~freader();
    size_t read_segment(size_t sz, std::vector<unsigned char> &bytes);
    void read_char(unsigned char &c);
    void restart();

private:
    FILE *file;
};

#endif //HUFFMAN_FREADER_H
