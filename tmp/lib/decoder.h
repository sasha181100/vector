//
// Created by pokerstar on 15.06.19.
//

#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct decoder {
public:
    static unsigned const int N = 256;
    decoder();
    void decode(vector<unsigned char> &inp, vector<unsigned char> &outp);
    void set_frec(vector<int> &);
    void build();
    void cnt_codes();
    void decode_tail(int, vector<unsigned char> &);


private:
    int frec[N];
    unsigned char cd[2 * N];
    vector<bool> codes[N];
    //void cnt_codes(int, vector<bool>);
    void dfs(int, vector<bool>);
    int par[2 * N];
    pair<int, int> chl[2 * N];
    unsigned char tail;
    int leaf[2 * N];
    vector<bool> now_code;
    int root;
    int cur_ver;
};
#endif //HUFFMAN_DECODER_H
