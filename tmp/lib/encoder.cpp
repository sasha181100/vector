//
// Created by watson on 13.06.19.
//

#include "encoder.h"
#include <set>
#include <iostream>
#include <algorithm>

typedef long long ll;

using namespace std;
encoder::encoder() {
    for (size_t i = 0; i < 2 * N; i++) {
        par[i] = -1;
        chl[i] = {-1, -1};
        if (i < N) {
            frec[i] = 0;

        }
    }
}
void encoder::build() {
    set<pair<int, int>> lst;
    size_t num = 0;
    for (int i = 0; i < N; i++) {
        if (frec[i] != 0) {
            lst.insert({frec[i], num});
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
    vector<bool> code;
    if (root == 0) {
        codes[cd[lst.begin()->second]].push_back(0);
    } else {
        cnt_codes(root, code);
    }
}
void encoder::cnt_codes(int v, vector<bool> code) {
    if (v < 0) return;
    if (chl[v].first == -1) {

        codes[cd[v]] = code;
    } else {
        code.push_back(0);
        cnt_codes(chl[v].first, code);
        code[code.size() - 1] = 1;
        cnt_codes(chl[v].second, code);
        code.pop_back();
    }
}

void encoder::compress(vector<unsigned char> const &in, vector<bool> &out) {
    for (size_t i = 0; i < in.size(); i++) {
        for (size_t j = 0; j < codes[in[i]].size(); j++) {
            out.push_back(codes[in[i]][j]);
        }
    };
}

void encoder::count_frec(vector<unsigned char> const&a) {
    for (size_t i = 0; i < a.size(); i++) {
        frec[a[i]]++;
    }
}

long long encoder::count_encoded_length() {
    long long res = 0;
    for (int i = 0; i < N; i++) {
        if (frec[i] != 0) {
            res += (ll) (frec[i] * codes[i].size());
        }
    }
    return res;
}

vector<int> encoder::get_frec() {
    vector<int> res;
    for (size_t i = 0; i < N; i++) {
        res.push_back(frec[i]);
    }
    return res;
}