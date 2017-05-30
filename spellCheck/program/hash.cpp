//
//  hash.cpp
//  hash
//
//  Created by Angel on 9/18/15.
//  Copyright (c) 2015 Angel. All rights reserved.
//

#include "hash.h"

//hash table primes
static unsigned int primes[9]={24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469};

// The constructor initializes the hash table.
// Uses getPrime to choose a prime number at least as large as
// the specified size for the initial size of the hash table.
hashTable:: hashTable(int size){
    filled=0;
    data.resize(capacity=getPrime(size));
    for (int n=0; n<capacity;n++) {
        data[n].isDeleted=false;
        data[n].isOccupied=false;
    }
}

// Insert the specified key into the hash table.
// If an optional pointer is provided,
// associate that pointer with the key.
// Returns 0 on success,
// 1 if key already exists in hash table,
// 2 if rehash fails.
int hashTable::insert(const std::string &key, void *pv){
    //Rehash if half full
    if (filled > (capacity/2)) {
        if (rehash()==false){
            return 2;
        }
    }
    int n=hash(key);
    //Linear Porbing
    while (data[n].isOccupied){
        if (data[n].key==key){
            return 1;
        }
        else{
            n++;
            if(n==capacity){
                n=0;
            }
        }
    }
    data[n].key=key;
    data[n].isOccupied=true;
    filled++;
    return 0;
}

// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const std::string &key){
    int n=findPos(key);
    if (n<0){
        return false;
    }
    else{
        return !data[findPos(key)].isDeleted;
    }
}

// Get the pointer associated with the specified key.
// If the key does not exist in the hash table, return NULL.
// If an optional pointer to a bool is provided,
// set the bool to true if the key is in the hash table,
// and set the bool to false otherwise.
/*
void hashTable::*getPointer(const std::string &key, bool *b){
 int n = findPos(key);
    if (n<0) {
        if (b != NULL){
            *b=false;
        }
        return NULL;
    }
    else{
        if (b !=NULL){
            *b=true;
        }
        return data[n].pv;
    }
}
*/

// Set the pointer associated with the specified key.
// Returns 0 on success,
// 1 if the key does not exist in the hash table.
int hashTable::setPointer(const std::string &key, void *pv){
    int n = findPos(key);
    if (n<0) {
        return 1;
    }
    else {
        data[n].pv = pv;
        return 0;
    }
}

// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.
bool hashTable::remove(const std::string &key){
    int n=findPos(key);
    if (n<0) {
        return false;
    }
    else{
        data[n].isDeleted=true;
        return true;
    }
}

// The hash function.
int hashTable::hash(const std::string &key){
    unsigned int hashVal=0;
    for (int n = 0; n < key.size(); n++){
        hashVal = 37*hashVal + key[n];
    }
    return hashVal % capacity;

}

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const std::string &key){
    int n=hash(key);
    //Linear probing
    while (data[n].isOccupied) {
        if (data[n].key==key) {
            return n;
        }
        else{
            n++;
            if(n==capacity){
                n=0;
            }
        }
    }
    return -1;
}

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash(){
    std::vector<hashItem> data1 = data;
    data.clear();
    data.resize(capacity=getPrime(this->capacity));
    filled =0;
    for (std::vector<hashItem>::iterator itr = data1.begin(), end = data1.end(); itr != end; itr++){
        if (itr->isOccupied && !itr->isDeleted){
            insert(itr->key);
        }
    }
    return true;
}

// Return a prime number at least as large as size.
// Uses a precomputed sequence of selected prime numbers.
unsigned int hashTable::getPrime(int size){
    for (static unsigned int* tablesize = primes; tablesize != NULL; tablesize++){
        if (size < *tablesize){
            return *tablesize;
        }
    }
    return 6291469;
}
