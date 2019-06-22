//
// Created by watson on 13.06.19.
//

#include "../utility/file_work.h"
#include <fstream>
#include <iostream>
#include "test.h"
#include "../utility/freader.h"
#include "../utility/fwriter.h"


void correctness() {
    compress("input.txt", "compressed_input.txt");
    decompress("compressed_input.txt", "output.txt");

    freader fin1("input.txt", "r");
    freader fin2("output.txt", "r");
    bool correct = 1;
    std::vector<unsigned char> bytes1, bytes2;

    while (fin1.read_segment(8192, bytes1)) {
        fin2.read_segment(8192, bytes2);
        if (bytes1 != bytes2) {
            correct = 0;
            //break;
        }
    }
    if (fin1.read_segment(8192, bytes1) != fin2.read_segment(8192, bytes2)) {
        correct = 0;
    }


    if (correct) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
}

void end_of_test(std::ofstream &out) {
    out.close();
    correctness();
    out.open("input.txt");
}



void test() {
    std::ofstream fout("input.txt");


    fout << "";
    end_of_test(fout);
    fout << "a";
    end_of_test(fout);
    fout << "abc";
    end_of_test(fout);
    fout << "aksdjhjfhgkjdfhg12312317238128371i273812738172831";
    end_of_test(fout);
    for (int i = 0; i < 123470; i++) {
        fout << "b";
    }
    //alsdkjgha;ioq[rgi smdf,n asiuw4833333hirejkgnf
    end_of_test(fout);
    for (int i = 0; i < 9000; i++) {
        fout << "abcd";
    }
    end_of_test(fout);
    for (int i = 0; i < 100; i++) {
        fout << "0123456789qwertyuiop[]asdfghjkl;'zxcvbnm,.../ /*-!@#$%^&*()";
    }
    end_of_test(fout);
    for (int i = 0; i < (1<<10); i++) {
        fout << (char)(rand() % 256);
    }
    end_of_test(fout);
    for (int i = 0; i < (1<<20); i++) {
        fout << (char)(rand() % 256);
    }
    end_of_test(fout);
}
