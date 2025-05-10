#include <iostream>
#include <stdint.h>
#include <fstream>
#include <string>
#include <cstdio>  // or <stdio.h>

using namespace std;

const int BLOCK_SIZE = 512;

//magic number in ASCII to put at beginning of each index file
const uint8_t MAGIC[8] = {'4', '3', '4', '8', 'P', 'R', 'J', '3'};

//----prof given functions----
int is_bigendian() {
    int x = 1;
    return ((uint8_t *)&x)[0] != 1;
}

uint64_t reverse_bytes(uint64_t x) {
    uint8_t dest[sizeof(uint64_t)];
    uint8_t *source = (uint8_t*)&x;
    for(int c = 0; c < sizeof(uint64_t); c++)
        dest[c] = source[sizeof(uint64_t) - c - 1];
    return *(uint64_t *)dest;
}
//----------------------------

bool file_exists(string& filename) {   //check if file exists or not
    FILE* file = fopen(filename.c_str(), "rb");
    if(file){   //file exists if you can open it successfully
        fclose(file);
        return true;
    }
    return false;
}

void write_uint64_big_endian(uint64_t value, uint8_t* dest) {  //write block ids to file
    if(!is_bigendian()){  //check if in correct form
        value = reverse_bytes(value);   //call other function prof gave if not in the right form
    }
    memcpy(dest, &value, sizeof(uint64_t));   //memcpy the block id to the given location in mem
}

void create_file(string& filename) {
    if(file_exists(filename)){   //check if file exists, exit if exists
        cout << "error: file '" << filename << "' already exists" << endl;
        exit(1);
    }

    ofstream out(filename, ios::binary);  //create a new file
    if(!out){
        cout << "error: could not create file" << endl;
        exit(1);
    }

    uint8_t block[BLOCK_SIZE] = {0};

    //copy magic number
    memcpy(block, MAGIC, 8);

    //root block ID: 0 bc file is empty
    write_uint64_big_endian(0, block + 8);

    //next block ID: 1 bc 0+1=1
    write_uint64_big_endian(1, block + 16);

    out.write(reinterpret_cast<char*>(block), BLOCK_SIZE);  //need to cast uint_8* to char* before writing
    out.close();

    cout << "created index file '" << filename << "'" << endl;
}

void insert_file(string& filename, unsigned int key, unsigned int value){} 
void search_file(string& filename, unsigned int key){}  
void load_file(string& filename, string& inputFilename){}  
void print_file(string& filename){} 
void extract_file(string& filename, string& outputFilename){}  

int main(int argc, char* argv[]) {
    string command = argv[1];

    if (command == "create" && argc == 3) { //ex: project3 create test.idx
        string filename = argv[2];
        create_file(filename);
    } 
    else if(command == "insert" && argc == 5){ //ex: project3 insert test.idx 15 100
        string filename = argv[2];
        insert_file(filename, (unsigned int)argv[3], (unsigned int)argv[4]);
    }
    else if(command == "search" && argc == 4){ //ex: project3 search test.idx 15
        string filename = argv[2];
        search_file(filename, (unsigned int)argv[3]);
    }
    else if(command == "load" && argc == 4){ //ex: project3 load test.idx input.csv
        string filename = argv[2];
        string inputFile = argv[3];
        load_file(filename, inputFile);
    }
    else if(command == "print" && argc == 3){ //ex: project3 print test.idx
        string filename = argv[2];
        print_file(filename);
    }
    else if(command == "extract" && argc == 4){ //ex: project3 extract test.idx output.csv
        string filename = argv[2];
        string outputFile = argv[3];
        extract_file(filename, outputFile);
    }
    else {
        cout << "error: unknown command" << endl;
        return 1;
    }

    return 0;
}
