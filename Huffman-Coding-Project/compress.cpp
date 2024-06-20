#include "HCTree.hpp"
#include "Helper.hpp"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int lowerBytes(int frq){
    if (frq < (1 << 8)){
        return 1;
    }

    if (frq < (1 << 16)){
        return 2;
    }

    return 3;
}

int main(int argc, char *argv[]){
    vector<int> freqs(256, 0);
    if (argc != 3){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }

    FancyInputStream input(argv[1]);

    if (!input.good()){
        cerr << "Error: Input file not open " << argv[1] << endl;;
        return 1;
    }

    FancyOutputStream output(argv[2]);

    if (!output.good()){
        cerr << "output error" << argv[2] << endl;
        return 1;
    }
    int filesize = input.filesize();
    input.reset();
    unsigned char symbol;

    if(filesize == 0){
        //output.write_byte(0);
        output.flush();
        return 0;
    }

    output.write_int(filesize);

    for (int i = 0; i < filesize; ++i){
        symbol = input.read_byte();
        freqs[symbol]++;
    }

    HCTree hftree;
    hftree.build(freqs);

    for (int i = 0; i < 256; ++i){
        int freq = freqs[i];
        int ebytes = lowerBytes(freq);
        output.write_byte((unsigned char)(ebytes));
        for(int j = 0; j < ebytes; ++j){
            output.write_byte((freq >> (j*8)) & 0xFF);
        }
    }

    input.reset();
    for(int i = 0; i < filesize; ++i){
        symbol = input.read_byte();
        hftree.encode(symbol, output);
    }

    output.flush();
    return 0;

}




