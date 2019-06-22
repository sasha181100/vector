//
// Created by pokerstar on 15.06.19.
//

#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include <iostream>
#include <vector>

using namespace std;

struct encoder {
    static const int N = 256;
    encoder();
    void compress(vector<unsigned char> &, vector<bool> &);
    void build();
    vector<bool> codes[N];
    void count_frec(vector<unsigned char> &);
    long long count_encoded_length();
    vector<int> get_frec();
private:
    int frec[N];
    unsigned char cd[2 * N];
    void cnt_codes(int, vector<bool>);
    int par[2 * N];
    pair<int, int> chl[2 * N];
    int root;
};

#endif //HUFFMAN_ENCODER_H
