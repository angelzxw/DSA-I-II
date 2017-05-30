//
//  spellcheck.cpp
//  hash
//
//  Created by Angel on 9/18/15.
//  Copyright (c) 2015 Angel. All rights reserved.
//

#include "spellcheck.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include "hash.h"
using namespace std;

//Load the data to hashtable from an input file
void LoadHashTable(hashTable &Dictionary){
    
    string filename;
    cout << "Enter name of dictionary: ";
    cin >> filename;
    
    ifstream input(filename.c_str());
    if (!input) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }
    
    // Load the data and clock the loading time
    clock_t T1 = clock();
    string line;
    while (getline(input, line)) {
        //convert to lower-case and insert to hashTable
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        Dictionary.insert(line);
    }
    clock_t T2 = clock();
    double time = ((double) (T2 - T1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << time << endl;
    input.close();
}

// Run spellcheck of a given input file and output the data to a specified file
void Check(ifstream &input, ofstream &output, hashTable &Dictionary){
    
    int linenum=1;//Counting line number
    bool runcheck=true;//Check the word unless it contains digits or more than 20 characters
    char ch;//Character read from input
    string line;//Contains vaild characters for a word
    
    while (input.good()) {
        input.get(ch);
        ch=tolower(ch);
        if (!input.eof() && ((ch>='a' && ch<='z') || ch == '-' || ch == '\'')) {
            line.push_back(ch);
        }
        else if (!input.eof() && ch>='0' && ch<='9') {
            line.push_back(ch);
            runcheck=false;
        }
        else {
            if (line.size()>20) {
                output << "Long word at line " << linenum << ", starts: " << line.substr(0,20) << endl;
                runcheck=false;
            }
            else if(runcheck){
                if (!line.empty() && !Dictionary.contains(line)){
                    output << "Unknown word at line " << linenum << ": " << line << endl;
                }
            }
            if (ch=='\n'){
                linenum++;
            }
            line.clear();
            runcheck=true;
        }
    }
}

// Take input data runing spellcheck and output the data to a specified file
void CheckAndWriteOutput(hashTable &Dictionary) {
    
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    ifstream input(filename.c_str());
    if (!input) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }
    
    cout << "Enter name of output file: ";
    cin >> filename;
    ofstream output(filename.c_str());
    if (!output) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }
    
    // Check and clock the checking time
    clock_t T1 = clock();
    Check(input, output, Dictionary);
    clock_t T2 = clock();
    double time = ((double) (T2 - T1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to check document: " << time << endl;
    
    input.close();
    output.close();

}

int main(int argc, const char * argv[]) {
    
    hashTable Dictionary(0);
    LoadHashTable(Dictionary);
    CheckAndWriteOutput(Dictionary);
    return 0;
    
}
