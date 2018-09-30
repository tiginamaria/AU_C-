#include <iostream>
#include <stdio.h>
#include <string>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include "huffman.h"

int main(int argc, char **argv) {
	bool archive = 0, unarchive = 0;
	std::string filein, fileout;
	int i = 1;
	while (i < argc) {
    	if(!strcmp(argv[i], "-c"))
			archive = 1;
		if(!strcmp(argv[i], "-u"))
			unarchive = 1;
		if(!strcmp(argv[i], "-f") || !strcmp(argv[i], "--file")) {
			i++;
			filein = argv[i];
		}
		if(!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")){
			i++;
			fileout = argv[i];
		}
		i++;
	}
	if (archive) {
		std::ifstream in_1(filein);
		in_1 >> std::noskipws;
		std::ofstream out_1(fileout, std::ofstream::binary);
		Archiver a_1;
		a_1.coder(in_1, out_1);
	}
	if (unarchive) {
		std::ifstream in_2(filein, std::ifstream::binary);
		std::ofstream out_2(fileout);
		Archiver a_2;
		a_2.decoder(in_2, out_2);
	}
}
	
	
