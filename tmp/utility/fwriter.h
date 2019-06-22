//
// Created by pokerstar on 15.06.19.
//

#ifndef HUFFMAN_FWRITER_H
#define HUFFMAN_FWRITER_H

#include <vector>
#include <cstdio>

using namespace std;

struct fwriter {
    fwriter(char *name, char *md);
    ~fwriter();
    void write_segment(vector<unsigned char> &bytes);
    void write_segment(vector<bool> &bools);
    void write_tail();
    void write_char(unsigned char &);
    void write_segment(vector<int> &ints);
private:
    FILE *file;
    unsigned char tail = 0;
    size_t remain_bites = 8;
};

#endif //HUFFMAN_FWRITER_H
