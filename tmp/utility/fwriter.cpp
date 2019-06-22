//
// Created by watson on 14.06.19.
//

#include "fwriter.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>

fwriter::fwriter(char *name, char *md) {
    file = fopen(name, md);
    if (file == nullptr) {
        throw std::runtime_error("while opening");
    }
}

void fwriter::write_segment(vector<unsigned char> &seg) {
    if (seg.size() != 0) {
        fwrite(seg.data(), sizeof(unsigned char), seg.size(), file);
    }
    if (ferror(file)) {
        throw std::runtime_error("error while writing");
    }
}

void fwriter::write_segment(vector<bool> &bools) {
    for (size_t i = 0; i < bools.size(); i++) {
        tail <<= 1;
        tail += bools[i];
        remain_bites--;
        if (remain_bites == 0) {
            write_char(tail);
            tail = 0;
            remain_bites = 8;
        }
    }
}

void fwriter::write_char(unsigned char &c) {
    fwrite(&c, 1, 1, file);
}

void fwriter::write_tail() {
    if (remain_bites != 8) {
        tail <<= remain_bites;
        write_char(tail);
    }
}

void fwriter::write_segment(vector<int> &seg) {
    fwrite(seg.data(), sizeof(int), seg.size(), file);
    if (ferror(file)) {
        throw std::runtime_error("error while writing");
    }
}


fwriter::~fwriter() {
    fclose(file);
}
