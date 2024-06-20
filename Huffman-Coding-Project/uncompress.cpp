#include "Helper.hpp"
#include "HCTree.hpp"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]){
    if (argc != 3){
        cerr << "Usage: " << argv[0] << " <compressed file> <output file>" << endl;
        return 1;
    }

    FancyInputStream input(argv[1]);
    if (!input.good()){
        cerr << "Error: Compressed file not opening " << argv[1] << endl;
        return 1;
    }

    FancyOutputStream output(argv[2]);
    if (input.filesize() == 0){
        return 0;
    }

    int originalFileSize = input.read_int();
    vector<int> freqs(256,0);

    for (int i = 0; i < 256; ++i){
        int freq = 0;
        int ebytes = input.read_byte();
        for(int j = 0; j < ebytes; ++j){
            freq |= input.read_byte() << (j*8);
        }
        freqs[i] = freq;
    }

    HCTree hftree;
    hftree.build(freqs);

    if (!output.good()){
        cerr << "Error: ouput file not open" << argv[2] << endl;
        return 1;
    }

    for(int i = 0; i < originalFileSize; ++i){
        unsigned char ds = hftree.decode(input);
        output.write_byte(ds);
    }

    output.flush();
    return 0;

}
