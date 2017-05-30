// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2015

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

using namespace std;

// A simple class; each object holds one string
class Data {
public:
    string data;
    Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    
    ifstream input(filename.c_str());
    if (!input) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }
    
    // The first line indicates the size
    string line;
    getline(input, line);
    stringstream ss(line);
    int size;
    ss >> size;
    
    // Load the data
    for (int i = 0; i < size; i++) {
        string line;
        getline(input, line);
        l.push_back(new Data(line));
    }
    
    input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
    string filename;
    cout << "Enter name of output file: ";
    cin >> filename;
    
    ofstream output(filename.c_str());
    if (!output) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }
    
    // Write the size first
    long size = l.size();
    output << size << endl;
    
    // Write the data
    for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
        output << (*ipD)->data << endl;
    }
    
    output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
    list<Data *> theList;
    loadDataList(theList);
    
    cout << "Data loaded.  Executing sort..." << endl;
    
    clock_t t1 = clock();
    sortDataList(theList);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    
    cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;
    
    writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

int i, j, k, size;
list<Data *> l2;
list<Data *>::iterator it, it1, ittmp, ipD;
float num;
Data *idx[1000000];
char  val[1000000];

class Number {
public:
    Data * pointer;
    unsigned long long front;
    int size;
};

void insertion(list<Data *> &l){
    for (it=l.begin(); it!=l.end(); it++){
        it1 = it;
        ittmp = it1;
        ittmp--;
        while(it1 != l.begin() && ((*it1)->data) < ((*ittmp)->data)){
            iter_swap(it1, ittmp);
            ittmp--;
            it1--;
        }
    }
}
void countingsort(list<Data *> &l){
    it = l.begin();
    while(it != l.end()){
        num = 1000*atof(((*it)->data).c_str());
        idx[(int)num] = *it;
        val[(int)num]++;
        it++;
    }
    k=0;
    while(k < 1000000){
        while(val[k]--)
            l2.push_back(idx[k]);
        k++;
    }
    l.swap(l2);
}


Number listdata[1000000];

inline bool compare(const Number &first, const Number &second){
    if (first.size != second.size){
        return first.size < second.size;
    } else{
        return first.front < second.front;
    }
}

void sortDataList(list<Data *> &l) {
    ipD=l.begin();
    ittmp=ipD++;
    
    //T3
    if ((*ipD)->data.length()<8){
        countingsort(l);
    }
    //T4:insertion sort for close-to-sorted list
    else if (!(((*ipD)->data.substr(0,6)).compare((*(ittmp))->data.substr(0,6)))){
        insertion(l);
    }
    //T1&T2:use sort() provided by c++
    else{
        it = l.begin();
        size = l.size();
        
        for (i = 0; i < size; ++i){
            listdata[i] = Number();
            j = (*it)->data.find('.');
            listdata[i].pointer = (*it);
            listdata[i].size = j;
            listdata[i].front = strtoull((*it)->data.substr(0,j-2).c_str(),0,10);
            it++;
        }

        sort(listdata, listdata+size, compare);
        
        it = l.begin();
        ittmp = l.end();
        i = 0;
        while (it != ittmp){
            *it = listdata[i].pointer;
            i++;
            it++;
        }
    }
}