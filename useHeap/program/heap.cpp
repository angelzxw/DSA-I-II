//
// This program allows the user to manipulate a binary heap.
// The program only inserts string ids with associated keys
// into the heap. The heap class, however, is capable of storing
// arbitrary pointers along with each heap item.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include "heap.h"

using namespace std;

//
// heap - The constructor allocates space for the nodes of the heap
// and the mapping (hash table) based on the specified capacity
//
heap::heap(int capacity){
    data.resize(capacity+1);
    mapping=new hashTable(capacity*2);
    this->capacity=capacity;
    this->filled=0;
}
    
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
int heap::insert(const std::string &id, int key, void *pv){
    if (filled==capacity) {
        return 1;
    }
    if (mapping->contains(id)) {
        return 2;
    }
    
    filled++;
    data[filled].id=id;
    data[filled].key=key;
    data[filled].pData=pv;
    
    mapping->insert(id, &data[filled]);
    percolateUp(filled);
    return 0;

}
    
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
int heap::setKey(const std::string &id, int key){
    //determine node with the given id does not exist
    bool isContained=true;
    
    node *pn=static_cast<node *>(mapping->getPointer(id,&isContained));
    if (!isContained) {
        return 1;
    }
    
    int posCur=getPos(pn);
    int oldkey=(*pn).key;
    
    data[posCur].key=key;
    if (key>oldkey) {
        percolateDown(posCur);
    }
    else if (key<oldkey) {
        percolateUp(posCur);
    }
    
    return 0;
};
    
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
int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if (filled==0){
        return 1;
    }
    
    if (pId) {
        *pId=data[1].id;
    }
    if (pKey) {
        *pKey=data[1].key;
    }
    if (ppData) {
        *(static_cast<void **>(ppData))=data[1].pData;
    }
    
    mapping->remove(*pId);
    data[1]=data[filled];
    filled--;
    percolateDown(1);
    
    return 0;
}
    
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
int heap::remove(const std::string &id, int *pKey, void *ppData){
    bool isContained=true;//check if specified id exists
    node *pn=static_cast<node *>(mapping->getPointer(id,&isContained));
    if (!isContained) {
        return 1;
    }
    int posCur=getPos(pn);
    
    //Optinal functions for if supplied pKey or ppData
    if (pKey) {
        *pKey=(*pn).key;
    }
    if (ppData) {
        *(static_cast<void **>(ppData))=(*pn).pData;
    }
    
    //remove the node with the given id from the hash table and the binary heap
    mapping->remove(id);
    data[posCur]=data[filled];
    mapping->setPointer(data[posCur].id, &data[posCur]);
    filled--;
    if (data[posCur].key>(*pKey)) {
        percolateDown(posCur);
    }
    if (data[posCur].key<(*pKey)) {
        percolateUp(posCur);
    }
    return 0;
}
    
// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int heap::getPos(node *pn){
    int pos =pn - &data[0];
    return pos;
}

// Restore the heap property traversing or down the heap
void heap::percolateDown(int posCur){
    node tmp=data[posCur];
    int keyCur=tmp.key;
    int child;
    for (child=posCur; child*2<=filled; posCur=child) {
        child=posCur*2;
        //If current node has two children
        if (child!=filled && data[child+1].key<data[child].key){
            child++;
        }
        if (data[child].key<keyCur) {
            data[posCur]=data[child];
            mapping->setPointer(data[posCur].id, &data[posCur]);
        }
        else
            break;
    }
    data[posCur]=tmp;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

// Restore the heap property traversing or up the heap
void heap::percolateUp(int posCur){
    node tmp=data[posCur];
    int hole;
    for (hole=posCur; hole>1 && tmp.key<data[hole/2].key; hole/=2) {
        data[hole]=data[hole/2];
        mapping->setPointer(data[hole].id, &data[hole]);
    }
    data[hole]=tmp;
    mapping->setPointer(data[hole].id, &data[hole]);
}
