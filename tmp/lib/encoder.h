//
// Created by pokerstar on 15.06.19.
//

#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include <iostream>
#include <vector>


struct encoder {
    static const int N = 256;
    encoder();
    void compress(std::vector<unsigned char> const&, std::vector<bool> &);
    void build();
    std::vector<bool> codes[N];
    void count_frec(std::vector<unsigned char> const&);
    long long count_encoded_length();
    std::vector<int> get_frec();
private:
    int frec[N];
    unsigned char cd[2 * N];
    void cnt_codes(int, std::vector<bool>);
    int par[2 * N];
    std::pair<int, int> chl[2 * N];
    int root;
};

#endif //HUFFMAN_ENCODER_H
