//
//  ShortestPath.cpp
//  DSA_Project3
//
//  Created by Angel on 11/18/15.
//  Copyright © 2015 Angel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include "graph.h"

using namespace std;

int main(){
    string filein, StartId, fileout, fileout2;
    cout<<"Enter name of graph file: ";
    cin>>filein;
    
    ifstream input(filein.c_str());
    
    graph graph(input);
    
    cout<<"Enter a valid vertex id for the staring vertex: ";
    cin>>StartId;
    
    while(!graph.contains(StartId)){
        cout<<"Enter a valid vertex id for the staring vertex: ";
        cin>>StartId;
    }
    
    clock_t t1 = clock();
    graph.dijkstra(StartId);
    cout<<"good"<<endl;
    clock_t t2 = clock();
    
    cout<<"Total time (in seconds) to apply Dijkstra's algorithm: ";
    cout<<double(t2 - t1)/CLOCKS_PER_SEC<<endl;
    
    cout<<"Enter name of output file: ";
    cin>>fileout;
    ofstream output(fileout.c_str());
    
    graph.printOutput(output);
    
    input.close();
    output.close();
    return 0;
}