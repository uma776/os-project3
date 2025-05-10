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

void write_val(uint64_t value, uint8_t* dest) {  //write block ids to file
    if(!is_bigendian()){  //check if in correct form
        value = reverse_bytes(value);   //call other function prof gave if not in the right form
    }
    memcpy(dest, &value, sizeof(uint64_t));   //memcpy the block id to the given location in mem
}

bool file_is_valid(string& filename) {
    ifstream in(filename, ios::binary);
    if(!in){   //if file dne
        return false;
    }
    
    char magic[8];
    in.read(magic, 8);  //read in magic number and make sure its a valid index file
    return string(magic, 8) == "4348PRJ3";
}

uint64_t read_val(ifstream& in) {
    uint64_t value;
    in.read(reinterpret_cast<char*>(&value), sizeof(value));

    if (!is_bigendian()) {   //check if val is in correct form
        value = reverse_bytes(value);   //convert if not
    }

    return value;
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
    write_val(0, block + 8);

    //next block ID: 1 bc 0+1=1
    write_val(1, block + 16);

    out.write(reinterpret_cast<char*>(block), BLOCK_SIZE);  //need to cast uint_8* to char* before writing
    out.close();

    cout << "created index file '" << filename << "'" << endl;
}

void insert_file(string& filename, unsigned int key, unsigned int value){} 

void search_file(string& filename, unsigned int key){
    if (!file_is_valid(filename)) {  //check if file is valid
        cout << "error: invalid or missing index file" << endl;
        exit(1);
    }

    ifstream in(filename, ios::binary);
    in.seekg(8); //skip magic number(first 8 bytes of file)

    uint64_t root_block = read_val(in);   //get val of root node

    if(root_block == 0){
        cout << "index is empty" << endl;
        return;
    }

    cout << "search_file(): searching for key " << key << " at root block " << root_block << endl;
    //TODO: add tree traversal logic
}  

void load_file(string& filename, string& inputFilename){
    if (!file_is_valid(filename)) {   //check if file is valid
        cout << "error: invalid or missing index file" << endl;
        exit(1);
    }

    ifstream csv(inputFilename);
    if (!csv.is_open()) {   //check if file opened before reading from it
        cout << "error: cannot open csv file" << endl;
        exit(1);
    }

    string line;
    while (getline(csv, line)) {  //while there are more key,value pairs
        char comma = line.find(',');   //find comma to separate key and value pair
        if(comma == string::npos){
            continue;
        }

        unsigned int key = std::stoull(line.substr(0, comma));   //get key from before the ,
        unsigned int value = std::stoull(line.substr(comma + 1));   //get value from after the ,

        std::cout << "load_file(): key: " << key << ", value: " << value << endl;

        insert_file(filename, key, value);   //insert key,value pairs into file
    }

    csv.close();
}  

void print_file(string& filename){
    if (!file_is_valid(filename)) {   //check if file is valid
        cout << "error: invalid or missing index file" << endl;
        exit(1);
    }

    ifstream in(filename, ios::binary);
    in.seekg(8); //skip magic number(first 8 bytes of file)

    uint64_t root_block = read_val(in);   //get val of root node

    if(root_block == 0){
        cout << "index is empty" << endl;
        return;
    }

    cout << "print_file(): tree traveral from root block " << root_block << endl;
    //TODO: add tree traversal logic and print key/value pairs
} 

void extract_file(string& filename, string& outputFilename){
    if (!file_is_valid(filename)) {   //check if file is valid
        cout << "error: invalid or missing index file" << endl;
        exit(1);
    }

    if (file_exists(outputFilename)) {   //check if output file exists
        cout << "error: output file already exists" << endl;
        exit(1);
    }

    ofstream out(outputFilename);
    if (!out.is_open()) {   //check if file opened before writing to it
        cout << "error: cannot open output file" << endl;
        exit(1);
    }

    ifstream in(filename, ios::binary);
    in.seekg(8);   //skip magic numbers

    uint64_t root_block = read_val(in);   //get val of root node

    if(root_block == 0){
        cout << "index is empty" << endl;
        return;
    }

    out << "key,value\n";
    out.close();

    cout << "extract_file(): extracted to " << outputFilename << endl;
}  

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
