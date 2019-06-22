//
// Created by pokerstar on 15.06.19.
//

#ifndef HUFFMAN_FREADER_H
#define HUFFMAN_FREADER_H
#include <vector>
#include <cstdio>

using namespace std;

struct freader {
    freader(char *name, char *md);
    ~freader();
    size_t read_segment(size_t sz, vector<unsigned char> &bytes);
    void read_char(unsigned char &c);
    void restart();

private:
    FILE *file;
};

#endif //HUFFMAN_FREADER_H
