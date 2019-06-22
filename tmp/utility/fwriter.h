//
// Created by pokerstar on 15.06.19.
//

#ifndef HUFFMAN_FWRITER_H
#define HUFFMAN_FWRITER_H

#include <vector>
#include <cstdio>



struct fwriter {
    fwriter(char const *name, char const *md);
    fwriter(fwriter const&) = delete;
    ~fwriter();
    void write_segment(std::vector<unsigned char> const &bytes);
    void write_segment(std::vector<bool> const &bools);
    void write_tail();
    void write_char(unsigned char const &chars);
    void write_segment(std::vector<int> const &ints);
private:
    FILE *file;
    unsigned char tail = 0;
    size_t remain_bites = 8;
};

#endif //HUFFMAN_FWRITER_H
