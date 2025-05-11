#include <iostream>
#include <stdint.h>
#include <fstream>
#include <string>
#include <cstdio>  // or <stdio.h>
#include <vector>

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

struct BTreeNode {   //class for a b tree node
    uint64_t block_id;
    uint64_t parent_id;
    uint64_t num_pairs;
    vector<uint64_t> keys;
    vector<uint64_t> values;
    vector<uint64_t> children;
    bool is_leaf() const {
        return children.empty();
    }
};

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
    if(!file_is_valid(filename)){  //check if file is valid
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

    //tree traversal logic
    uint64_t current_id = root_block;  //start at root node

    while(true){   //until we find key or reach a leaf
        BTreeNode node = read_node(in, current_id);

        for(int i = 0; i < node.keys.size(); i++){  //loop thru keys in current node
            if(key == node.keys[i]){   //if key found, print key/val pair
                cout << "found key " << key << ", value: " << node.values[i] << endl;
                return;
            }

            if(key < node.keys[i]){  //if true, then key could be in left child
                if(i < node.children.size()){  //make sure valid child exists
                    current_id = node.children[i];
                    goto next_node;  //jump past rest of while loop
                }
            }
        }

        //if not a leaf and key not found, go to rightmost node
        if((!node.is_leaf()) && (node.children.size() > node.keys.size())){
            current_id = node.children.back();
        } 
        else{
            cout << "key " << key << " not found" << endl;
            return;
        }

        next_node:;   //jump to this spot from earlier to skip rest of while loop
    }
}  

void load_file(string& filename, string& inputFilename){
    if(!file_is_valid(filename)){   //check if file is valid
        cout << "error: invalid or missing index file" << endl;
        exit(1);
    }

    ifstream csv(inputFilename);
    if(!csv.is_open()){   //check if file opened before reading from it
        cout << "error: cannot open csv file" << endl;
        exit(1);
    }

    string line;
    while(getline(csv, line)){  //while there are more key,value pairs
        char comma = line.find(',');   //find comma to separate key and value pair
        if(comma == string::npos){
            continue;
        }

        uint64_t key = stoull(line.substr(0, comma));   //get key from before the ,
        uint64_t value = stoull(line.substr(comma + 1));   //get value from after the ,

        cout << "load_file(): key: " << key << ", value: " << value << endl;

        insert_file(filename, key, value);   //insert key,value pairs into file
    }

    csv.close();
}  

void print_traversal(ifstream& in, uint64_t root_block){
    BTreeNode node = read_node(in, root_block);

    for(int i = 0; i < node.keys.size(); i++){  //loop thru keys in current node
        if(i < node.children.size()){  //recursively call print_traversal()
            print_traversal(in, node.children[i]);
        }

        cout << node.keys[i] << "," << node.values[i] << endl;
    }

    //go to rightmost child and recursively call print_traversal()
    if((!node.is_leaf()) && (node.children.size() > node.keys.size())){
        print_traversal(in, node.children.back());
    }
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

    print_traversal(in, root_block);
} 

void extract_file(string& filename, string& outputFilename){
    if(!file_is_valid(filename)){   //check if file is valid
        cout << "error: invalid or missing index file" << endl;
        exit(1);
    }

    if(file_exists(outputFilename)){   //check if output file exists
        cout << "error: output file already exists" << endl;
        exit(1);
    }

    ofstream out(outputFilename);
    if(!out.is_open()){   //check if file opened before writing to it
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

    if(command == "create" && argc == 3){ //ex: project3 create test.idx
        string filename = argv[2];
        create_file(filename);
    } 
    else if(command == "insert" && argc == 5){ //ex: project3 insert test.idx 15 100
        string filename = argv[2];
        uint64_t key = stoull(argv[3]);
        uint64_t value = stoull(argv[4]);
        insert_file(filename, key, value);
    }
    else if(command == "search" && argc == 4){ //ex: project3 search test.idx 15
        string filename = argv[2];
        uint64_t key = stoull(argv[3]);
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
    else{
        cout << "error: unknown command" << endl;
        return 1;
    }

    return 0;
}
