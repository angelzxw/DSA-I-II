//
//  graph.hpp
//  DSA_Project3
//
//  Created by Angel on 11/18/15.
//  Copyright © 2015 Angel. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <list>
#include "hash.h"
#include "heap.h"

class graph{
    
public:
    //
    // graph - The constructor initializes allocates space for the nodes of the heap
    // and the mapping (hash table) based on the specified input file
    //
    graph(); //default constructor
    graph(std::ifstream &input);
    
    //Initializes inpute file of vertices
    void initVertices(std::ifstream &input);
    
    // Returns true if the graph contains
    // the specified vertex
    // Returns False otherwise
    bool contains(std::string VertexId);
    
    //  Adds a vertex to the graph
    void addVertex(const std::string& VertexId);
    
    //  Applies dijsktra's algorithm to
    //  the graph at the specified
    //  starting vertex
    void dijkstra(const std::string& SourceId);
    
    // Writes output of dijkstra's algorithm
    // to the specified output file
    void printOutput(std::ofstream& output);
    
private:
    //An inner class within graph
    class Vertex;
    
    //An inner struct within graph
    struct edge {
    public:
        int weight;
        Vertex* next;
    };
    
    class Vertex {
        
    public:
        std::string id;
        std::list<edge*> edgelist;
        int minDist;
        Vertex* prev;
        bool known;
    };
    
    // The hashtable.
    hashTable *mapping;
    
    //The heap.
    heap *graphHeap;
    
    // The actual entries are here.
    std::list<Vertex*> data;
};
#endif /* graph_hpp */
