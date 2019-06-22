//
// Created by pokerstar on 16.06.19.
//

#include <iostream>
#include <cstring>
#include "utility/file_work.h"
#include "test/test.h"
using namespace std;

int main(int argc, char *argv[]) {
    int mode = 0;
    if (argc == 4) {
        if (strcmp(argv[1], "-e") == 0) {
            mode = 1;
        } else if (strcmp(argv[1], "-d") == 0) {
            mode = 2;
        } else {
            cout << "Incorrect mode" << endl << "info for more information";
            return 0;
        }
    }
    if (argc == 2) {
        if (strcmp(argv[1], "-t") == 0) {
            test();
            return 0;
        } else if (strcmp(argv[1], "-info") == 0) {
            //info
            cout << "Welcome to library for compression of Huffman.\nThere are 4 modes for working:\n   -e: encode input file in output file\n  -d: decode information from input file to output\n  -t: check the program on correctness\nHave a great time!";
            return 0;
        }
    }
    char *inp = argv[2];
    char *outp = argv[3];
    if (mode == 1) {
        try {
            compress(inp, outp);
        } catch (std::exception const &e) {
            cout << "error";
            return 0;
        }
    } else if (mode == 2) {
        try {
            decompress(argv[2], outp);
        } catch (std::exception const &e) {
            cout << "error";
            return 0;
        }
    } else {
        cout << "Incorrect numbers of args" << endl << "info for more information";
        return 0;
    }
}
