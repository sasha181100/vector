//
// Created by watson on 13.06.19.
//

#include "file_work.h"
#include "freader.h"
#include "../lib/encoder.h"
#include "fwriter.h"
#include "../lib/decoder.h"
#include <stdexcept>

void compress(char *input,  char *output) {

    freader in(input, "r");
    fwriter out(output, "w");
    vector<unsigned char> bytes;
    encoder a;
    while(in.read_segment(8192, bytes)) {
        a.count_frec(bytes);
    }

    a.build();

    vector<int> frec;
    frec = a.get_frec();

    out.write_segment(frec);

    unsigned char cnt_free_cells = (8 - a.count_encoded_length() % 8) % 8;
    out.write_char(cnt_free_cells);
    in.restart();
    bytes.clear();
    vector<bool> compress_bytes;
    while (in.read_segment(8192, bytes)) {
        a.compress(bytes, compress_bytes);
        out.write_segment(compress_bytes);
        bytes.clear();
        compress_bytes.clear();
    }
    out.write_tail();
}

void decompress(char *input, char *output) {

    freader in(input, "r");
    fwriter out(output, "w");
    decoder a;
    int x;
    vector<int> frec;
    unsigned char c;

    for (size_t i = 0; i < 256; i++) {
        x = 0;

        for (size_t j = 0; j < 4; j++) {
            in.read_char(c);
            x += (c << (j * 8));
        }
        frec.push_back(x);
    }

    bool empty = 1;
    for (size_t i = 0; i < 256; i++) {
        if (frec[i] != 0) {
            empty = 0;
            break;
        }

    }
    if (empty) {
        return;
    }
    unsigned char cnt_free_cells;

    in.read_char(cnt_free_cells);

    a.set_frec(frec);
    a.build();

    vector<unsigned char> bytes, decodebytes;
    int i = 0;

    while (in.read_segment(8192, bytes)) {
        if (i != 0) {
            a.decode_tail(0, decodebytes);
            out.write_segment(decodebytes);
            decodebytes.clear();
        }
        a.decode(bytes, decodebytes);
        out.write_segment(decodebytes);
        bytes.clear();
        decodebytes.clear();
        i++;
    }
    a.decode_tail(cnt_free_cells, decodebytes);
    out.write_segment(decodebytes);


}

