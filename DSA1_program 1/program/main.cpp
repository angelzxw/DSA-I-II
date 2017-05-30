/**
 *  program assignment 1
 *  Xiaowen Zhang
 *  This program allows the user to input text file containing proper commands, each command will direct the program to create a stack/queue, to push a value of int/double/string onto a stack/queue, or to pop a valur from a stack/queue.
 *
 **/
//
//  main.cpp
//  Created by ZXW on 4/5/15.
//  Copyright (c) 2015 ZXW. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "SimpleList.h"

using namespace std;

/**
 * Search the list holding SimpleList of given type (int/double/string) with the specified name.
 * This function returns the pointer to the SimpleList if it exists; otherwise, gives null pointer.
 */
template <typename T>
SimpleList<T>* search(list<SimpleList<T> *> lst, string name){
    typename list<SimpleList<T> *> ::iterator it;
    for (it=lst.begin(); it != lst.end(); ++it){
        if (name==(*it)->get_listname()){
            return *it;
        }
    }
    return nullptr;
}


/**
 * Create a new SimpleList
 */
template <typename T>
void create(string listName, string val,list<SimpleList<T> *> &lst){
    if (val.at(0)=='s'){
        SimpleList<T> *tmp = new Stack<T>(listName);
        lst.push_front(tmp);
    }
    else {
        SimpleList<T> *tmp = new Queue<T>(listName);
        lst.push_front(tmp);
    }
}

/**
 * Process "Create", "Push", or "Pop" command.
 */
template <typename T>
void process (string name, string val, T value, list<SimpleList<T> *> &lst, ofstream &file, char c){
    int valid;
    SimpleList<T> *prt=search(lst, name);
    if (prt == nullptr){
        valid=0;
    }
    else
        valid=1;
    switch (c){
            //"Create" command
        case 'r':
            if (valid){
                file<< "ERROR: This name already exists!"<<endl;
            }
            else
                create(name, val, lst);
            break;
            
            //Push command
        case 'u':
            if (valid){
                prt->push(value);
            }
            else
                file<< "ERROR: This name does not exist!"<<endl;
            break;
            
            //Pop command
        case 'o':
            if (valid){
                if (prt->empty()){
                    file<< "ERROR: This list is empty!"<<endl;
                }
                else{
                    T pop_val=prt->pop();
                    file<<"Value popped: "<<pop_val<<endl;
                }
            }
            else
                file<< "ERROR: This name does not exist!"<<endl;
            break;
    }
};


int main() {

    string line, input, output;
    ifstream myfile;
    cout << "Enter name of input file : " << endl;
    cin >> input;
    myfile.open(input.c_str());
    
    ofstream file;
    cout << "Enter name of output file : " << endl;
    cin >> output;
    file.open(output.c_str());
    
    
    list<SimpleList<int> *> listSLi; // all integer stacks and queues
    list<SimpleList<double> *> listSLd; // all double stacks and queues
    list<SimpleList<string> *> listSLs; // all string stacks and queues
    
    //Variables store listname and value from command lines
    string name, val;

    
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            file <<"PROCESSING COMMAND: "<<line << endl;
            
            /**
             *Parse and store name and valus from command line.
             */
            size_t pos=line.find(' ');
            size_t pos2 = line.find(' ', pos+1);
            char c=(line.at(1));
            
            //If command is "Creat" and "Push"
            if (c=='r'||c=='u'){
                name=line.substr(pos+1, pos2-(pos+1));
                val=line.substr(pos2+1);
            }
            //If command is "Pop"
            else
                name=line.substr(pos+1);
            
            //If it's Int type
            if (name.at(0)=='i'){
                int value=atoi(val.c_str());
                process(name, val, value, listSLi, file, c);
            }
            //If it's Double type
            else if(name.at(0)=='d'){
                double value=atof(val.c_str());
                process(name, val, value, listSLd, file, c);
            }
            //If it's String type
            else {
                process(name, val, val, listSLs, file, c);
            }
        }
        myfile.close();
    }
    else
        file << "Unable to open file"<< endl;
    
    file.close();
    return 0;
}


