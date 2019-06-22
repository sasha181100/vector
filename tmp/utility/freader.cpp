//
// Created by watson on 14.06.19.
//

#include "freader.h"
#include <cstdio>
#include <iostream>

freader::freader(char *name, char *md) {
    file = fopen(name, md);
    if (file == nullptr) {
        throw std::runtime_error("while opening");
    }
}

size_t freader::read_segment(size_t sz, vector<unsigned char> &seg) {
    seg.resize(sz);
    size_t cnt = fread(seg.data(), 1, sz, file);
    size_t x = seg.size();
    for (size_t i = 0; i < (x - cnt); i++) {
        seg.pop_back();
    }
    if (ferror(file)) {
        throw;
    }
    return cnt;
}
void freader::read_char(unsigned char &c) {
    fread(&c, 1, 1, file);
    if (ferror(file)) {
        throw;
    }
}
freader::~freader() {
    fclose(file);
}

void freader::restart() {
    rewind(file);
}