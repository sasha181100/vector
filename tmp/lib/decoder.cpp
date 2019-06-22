//
// Created by watson on 13.06.19.
//

#include "decoder.h"
#include <iostream>
#include <set>


using namespace std;

decoder::decoder() {
    for (int i = 0; i < 2 * N; i++) {
        par[i] = -1;
        chl[i] = {-1, -1};
        leaf[i] = -1;
    }
}

void decoder::set_frec(vector<int> &fr) {
    for (size_t i = 0; i < fr.size(); i++) {
        frec[i] = fr[i];
    }
}

void decoder::cnt_codes() {
    vector<bool> code;
    dfs(root, code);
}

void decoder::dfs(int v, vector<bool> code) {
    if (leaf[v] != -1) {
        codes[cd[v]] = code;
    } else {
        code.push_back(0);
        dfs(chl[v].first, code);
        code[code.size() - 1] = 1;
        dfs(chl[v].second, code);
        code.pop_back();
    }
}

void decoder::build() {
    set<pair<int, int>> lst;
    size_t num = 0;
    for (int i = 0; i < N; i++) {
        if (frec[i] != 0) {
            lst.insert({frec[i], num});
            leaf[num] = i;
            cd[num] = i;
            num++;
        }
    }
    pair<int, int> a1, a2;
    while (lst.size() > 1) {
        a1 = *lst.begin();
        lst.erase(a1);
        a2 = *lst.begin();
        lst.erase(a2);
        lst.insert({a1.first + a2.first, num});
        chl[num].first = a1.second;
        chl[num].second = a2.second;
        par[a1.second] = num;
        par[a2.second] = num;
        num++;
    }
    root = num - 1;
    cur_ver = root;
    vector<bool> code;
    if (root == 0) {
        codes[cd[lst.begin()->second]].push_back(0);
    } else {
        cnt_codes();
    }
}

void decoder::decode(vector<unsigned char> &in, vector<unsigned char> &out) {
    tail = in.back();
    if (root == 0) {
        for (size_t i = 0; i < 8 * (in.size() - 1); i++) {
            out.push_back(cd[0]);
        }
        return;
    }
    for (size_t i = 0; i < in.size() - 1; i++) {
        bool bit;
        for (int j = 7; j >= 0; j--) {
            bit = (in[i] >> j) & 1;
            if (bit) {
                cur_ver = chl[cur_ver].second;
            } else {
                cur_ver = chl[cur_ver].first;
            }
            if (leaf[cur_ver] != -1) {
                out.push_back(cd[cur_ver]);
                cur_ver = root;
            }
        }
    }
}


void decoder::decode_tail(int cnt_free_cells, vector<unsigned char> &out) {
    bool bit;
    if (root == 0) {
        for (size_t i = 0; i < 8 - cnt_free_cells; i++) {
            out.push_back(cd[0]);
        }
        return;
    }
    for (int j = 7; j >= cnt_free_cells; j--) {
        bit = (tail >> j) & 1;

        if (bit) {
            cur_ver = chl[cur_ver].second;
        } else {
            cur_ver = chl[cur_ver].first;
        }
        if (leaf[cur_ver] != -1) {
            out.push_back(cd[cur_ver]);
            cur_ver = root;
        }
    }
}

