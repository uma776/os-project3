#include <iostream>
#include <stdint.h>
#include <fstream>
#include <string>

using namespace std;

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

void create_file(string& filename) {}
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
        unsigned int key = (int)argv[3];
        unsigned int value = (int)argv[4];
        insert_file(filename, key, value);
    }
    else if(command == "search" && argc == 4){ //ex: project3 search test.idx 15
        string filename = argv[2];
        unsigned int key = (int)argv[3];
        search_file(filename, key);
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
