//
//  graph.cpp
//  DSA_Project3
//
//  Created by Angel on 11/18/15.
//  Copyright © 2015 Angel. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include "hash.h"
#include "heap.h"
#include "graph.h"
#define INF 1000000000
using namespace std;
//
// graph - The constructor initializes allocates space for the nodes of the heap
// and the hash table based on the specified input file
//
graph::graph(std::ifstream &input){
    mapping=new hashTable();
    initVertices(input);
    graphHeap= new heap(data.size());
    Vertex *vertextptr;
    std::list<Vertex *>::iterator it;
    //assign to unknown with infinit distance
    for(it = data.begin(); it != data.end(); it++){
        graphHeap->insert((*it)->id, INF, *it);
        vertextptr = *it;
        vertextptr->prev = NULL;
        vertextptr->known = false;
        vertextptr->minDist = INF;
        graphHeap->setKey(vertextptr->id, vertextptr->minDist);
    }
}

//Initializes inpute file of vertices
void graph::initVertices(ifstream &input){
    string line, v1, v2;
    int cost;
    bool isContained=true;//check if specified id exists;
    
    while(getline(input, line)){
        stringstream ss(line);
        string temp;
        //reading verteces and weight from the input file
        vector<string> graphdata;
        while(ss>>temp){
            graphdata.push_back(temp);
        }
        //if on line doesn't contain two vertecs and a weight number, then stop reading
        if(graphdata.size() != 3){
            break;
        }
        else{
            v1 = graphdata[0];
            v2 = graphdata[1];
            //convert string to an int
            istringstream sss(graphdata[2]);
            sss>>cost;
            
            if(!mapping->contains(v1)){
                addVertex(v1);
            }
            if(!mapping->contains(v2)){
                addVertex(v2);
            }
            
            Vertex *vertextptr = static_cast<Vertex *>(mapping->getPointer(v1, &isContained));
            
            //  Adds an edge to a Vertex
            edge *edgeptr=new edge;
            edgeptr->next = static_cast<Vertex *>(mapping->getPointer(v2, &isContained));
            edgeptr->weight = cost;
            vertextptr->edgelist.push_back(edgeptr);
            
        }
    }
}

// Returns true if the graph contains
// the specified vertex
// Returns False otherwise
bool graph::contains(std::string VertexId){
    return mapping->contains(VertexId);
}

//  Adds a vertex to the graph
void graph::addVertex(const std::string& VertexId){
    Vertex *vertextptr = new Vertex;
    vertextptr->id = VertexId;
    vertextptr->prev = NULL;
    mapping->insert(VertexId, vertextptr);
    data.push_back(vertextptr);
}

//  Applies dijsktra's algorithm to
//  the graph at the specified
//  starting vertex
void graph::dijkstra(const std::string& StartId){
    
    bool b;
    
    //set distance from source to source to be 0
    Vertex *v = static_cast<Vertex *>(mapping->getPointer(StartId, &b));
    v->minDist = 0;
    v->prev = NULL;
    v->known = false;
    graphHeap->setKey(v->id, v->minDist);
    
    Vertex *u;
    int d = 0;//temp weight
    
    string *pId=NULL;
    int *pKey=NULL;

    //dijsktra's algorithm
    while((graphHeap->deleteMin(pId, pKey, &u))==0){
        //deleteMin successes
        u->known = true;
        
        //for each neighbor vertece of u
        list<edge *>::iterator it;
        for(it=(u->edgelist).begin(); it != (u->edgelist).end(); it++){
            
            //for vertex v which has not yet been removed from edgelist
            Vertex *v = (*it)->next;
            if(! v->known){
                d=u->minDist+(*it)->weight;
                
                if(d < (v->minDist)){
                    //if a shorter path to v has been found
                    v->minDist = d;
                    v->prev = u;
                    graphHeap->setKey(v->id, v->minDist);
                }
            }
        }
    }
}

//  Writes output of dijkstra's algorithm
//  to a specified output file.
void graph::printOutput(std::ofstream& output){
    
    Vertex *vertextptr;
    list<string> nodes;
    int total;
    
    //iterate through each verteces
    list<Vertex *>::iterator it;
    for(it= data.begin(); it != data.end(); it++){
        vertextptr = *it;
        
        //insert the vertex at beginning of linked list, nodes
        nodes.push_back(vertextptr->id);
        
        //find smallest distance associated with the vertex
        total = vertextptr->minDist;
        
        if(total >= INF || total < 0){
            //if the vertex has 0 or INF distance, they it has no edge to other verteces
            output<<nodes.front()<<": NO PATH"<<endl;
        }
        else{
            while(vertextptr->prev != NULL){
                vertextptr = vertextptr->prev;
                
                //store all the verteces that have a edge to the given vertex
                nodes.push_front(vertextptr->id);
            }
            //print out the vertces associated with the given vertex
            list<string>::iterator itt = nodes.begin();
            output<<nodes.back()<<": "<<total<<" ["<<(*itt);
            itt++;
            while(itt != nodes.end()){
                output<<", "<<(*itt);
                itt++;
            }
            output<<"]"<< endl;
        }
        nodes.clear();
    }
}
