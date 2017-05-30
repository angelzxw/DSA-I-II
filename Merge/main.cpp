//
//  main.cpp
//  DSA_Project4
//
//  Created by Xiaowen (Angel) Zhang on 11/27/15.
//  Copyright © 2015 Angel. All rights reserved.
//
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class cell{
public:
    int index;
    int direction;
    cell(int idx, int dir): index(idx), direction(dir){}
};
const int Down=1;
const int Right=0;
const int Block=9;
string v1, v2, v3;
int i, j;

//initialize the matrix, grid
const cell defset(0, Block);
vector<cell> x(1001, defset);
vector< vector<cell> > grid(1001, x);

void check(string &v1, string &v2, string &v3, ofstream &output){
    
    int length1=v1.length(), length2=v2.length(), length3=v3.length();
    
    /*
    for(int j=0; j<length1+1;j++){
        for (int i=0; i<length2+1;i++){
            output<<grid[j][i].index<<"   ";
        }
        output<<endl;
    }
    output<<endl<<endl;
    
    for(int j=0; j<length1+1;j++){
        for (int i=0; i<length2+1;i++){
            output<<grid[j][i].direction<<"   ";
        }
        output<<endl;
    }
    output<<endl<<endl;
    */
    //int length1=v1.length(), length2=v2.length(), length3=v3.length();
    
    //check the the length: if the length doesn't match, then it must not be a merge
    if (length3 != length1 + length2){
        output<< "*** NOT A MERGE ***"<<endl;
        //output<<v1<<endl;
        //output<<v2<<endl;
        //output<<v3<<endl;
        //output<<"exist 1"<<endl;
    }
    else{
        v1=" "+v1;
        v2=" "+v2;
        v3=" "+v3;
        //Fill in the matrix
        for(j=0; j<length2+1;j++){
            for (i=0; i<length1+1;i++){
                //if the char matches and the index has to be the same as the position (i+j)
                if (i>0 && v3[i+j]==v1[i] && grid[i-1][j].index+1==i+j){
                    //assign index and direction
                    grid[i][j].index=grid[i-1][j].index+1;
                    grid[i][j].direction=Right;
                }
                if (j>0 && v3[i+j]==v2[j] && grid[i][j-1].index+1==i+j){
                    grid[i][j].index=grid[i][j-1].index+1;
                    grid[i][j].direction=Down;
                }
            }
        }
        
        /*
        for(j=0; j<length2+1;j++){
             for (i=0; i<length1+1;i++){
                 output<<grid[i][j].index<<"  ";
             }
             output<<endl;
         }
         output<<endl<<endl;
         for(j=0; j<length2+1;j++){
             for (i=0; i<length1+1;i++){
                 output<<grid[i][j].direction<<"  ";
             }
             output<<endl;
         }
         */
        //output<<"start discover"<<endl;
        
        
        //Discover the actual string through backtrack
        i = length1;
        j = length2;
        if (grid[i][j].direction==Block) {
            output<< "*** NOT A MERGE ***"<<endl;
            //output<<v1<<endl;
            //output<<v2<<endl;
            //output<<v3<<endl;
            //output<<"exist 2"<<endl;
        }
        
        /*
         else if(grid[i][j].index != length3){
         output<<v1<<endl;
         output<<v2<<endl;
         output<<v3<<endl;
         output<<grid[i][j].index<<endl;
         output<<length3<<endl;
         output<< "*** NOT A MERGE ***"<<endl;
         output<<"exist 2.5"<<endl;
         
         }*/
        
        else{
            while (i!=0 || j!= 0) {
                if (grid[i][j].direction == Right){
                    //Capitalize the character if the node is moving right
                    v3[i+j] = toupper(v3[i+j]);
                    i--;
                }
                else if (grid[i][j].direction == Down) {
                    j--;
                }
            }
            output<<v3.substr(1, length3)<<endl;
            //output<<"exist 3"<<endl;
        }
    }
    for(int j=0; j<1001;j++){
        for (int i=0; i<1001;i++){
            grid[i][j]=defset;
        }
    }
}

int main(){
    string filein, fileout, fileout2;
    cout<<"Enter name of graph file: ";
    cin>>filein;
    ifstream input(filein.c_str());
    
    cout<<"Enter name of output file: ";
    cin>>fileout;
    ofstream output(fileout.c_str());
    
    while (input>>v1) {
        input>>v2;
        input>>v3;
        check (v1, v2, v3, output);
    }
    input.close();
    output.close();
    return 0;
}
