//
//  heap.h
//  hash
//
//  Created by Angel on 9/30/15.
//  Copyright © 2015 Angel. All rights reserved.
//

#ifndef heap_h
#define heap_h

#include <vector>
#include <string>
#include "hash.h"

class heap{
    
public:
    //
    // heap - The constructor allocates space for the nodes of the heap
    // and the mapping (hash table) based on the specified capacity
    //
    heap(int capacity);
    
    //
    // insert - Inserts a new node into the binary heap
    //
    // Inserts a node with the specified id string, key,
    // and optionally a pointer. They key is used to
    // determine the final position of the new node.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is already filled to capacity
    //   2 if a node with the given id already exists (but the heap
    //     is not filled to capacity)
    //
    int insert(const std::string &id, int key, void *pv = NULL);
    
    //
    // setKey - set the key of the specified node to the specified value
    //
    // I have decided that the class should provide this member function
    // instead of two separate increaseKey and decreaseKey functions.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    //
    int setKey(const std::string &id, int key);
    
    //
    // deleteMin - return the data associated with the smallest key
    //             and delete that node from the binary heap
    //
    // If pId is supplied (i.e., it is not NULL), write to that address
    // the id of the node being deleted. If pKey is supplied, write to
    // that address the key of the node being deleted. If ppData is
    // supplied, write to that address the associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is empty
    //
    int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);
    
    //
    // remove - delete the node with the specified id from the binary heap
    //
    // If pKey is supplied, write to that address the key of the node
    // being deleted. If ppData is supplied, write to that address the
    // associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    //
    int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);

private:
    //An inner class within heap
    //Each node in the heap contains:
    // id - a string used as an id.
    // key - an integer used as a key.
    // pData - a pointer related to the actual data.
    //      NULL if no pointer was provided to insert.
    class node {
    public:
        std::string id;
        int key;
        void *pData;
    };
    
    int capacity; // The current capacity of the heap array.
    int filled; // Number of elements in heap.
    
    std::vector<node> data; // The actual entries are here.
    
    // The hashtable.
    hashTable *mapping;
    
    // Search for an item with the specified key.
    // Return the position if found, -1 otherwise.
    int getPos(node *pn);
    
    // Restore the heap property traversing or down the heap
    void percolateDown(int posCur);
    
    // Restore the heap property traversing or up the heap
    void percolateUp(int posCur);
    
};

#endif /* heap_h */