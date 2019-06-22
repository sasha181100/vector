//
// Created by pokerstar on 15.06.19.
//

#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H
#include <algorithm>
#include <iostream>
#include <vector>


struct decoder {
public:
    static unsigned const int N = 256;
    decoder();
    void decode(std::vector<unsigned char> const &inp, std::vector<unsigned char> &outp);
    void set_frec(std::vector<int> const&);
    void build();
    void cnt_codes();
    void decode_tail(int, std::vector<unsigned char> &);


private:
    int frec[N];
    unsigned char cd[2 * N];
    std::vector<bool> codes[N];
    //void cnt_codes(int, vector<bool>);
    void dfs(int, std::vector<bool>);
    int par[2 * N];
    std::pair<int, int> chl[2 * N];
    unsigned char tail;
    int leaf[2 * N];
    std::vector<bool> now_code;
    int root;
    int cur_ver;
};
#endif //HUFFMAN_DECODER_H
