//
//  SimpleList.h
//  hw
//
//  Created by ZXW on 4/5/15.
//  Copyright (c) 2015 ZXW. All rights reserved.
//

#ifndef __hw__SimpleList__
#define __hw__SimpleList__

#include <stdio.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdio>

using namespace std;

#endif /* defined(__hw__SimpleList__) */

//Base class: SimpleList
template <class List>
class SimpleList
{
private:
    struct Node{
        /**
         * The data contained in this node. We do not allow you to
         * modify node data, so it is const.
         */
        const List data;
        
        /**
         * A pointer to the next node in the list. May be NULL
         * if one does not exist.
         */
        Node *next;
        
        /**
         * Node constructor.
         */
        Node(const List &d =List{ }): data{d}
        {}
    };
    
private:
    string listName;
    int thisSize;
    Node *head;
    Node *tail;
    
public:
    /**
     * SimpleList constructor.
     */
    SimpleList (string listName) : listName(listName) {
         init();
    }
    
    /**
     * Access to listname
     */
    string get_listname() const{
        return listName;
    };
    
    /**
     * Push and Pop are implemented differently
     * for Stack and Queue classes.
     */
    virtual void push(const List & data)=0;
    virtual List pop()=0;
    
    /**
     * Get the size of the SimpleList.
     */
    int size() const{
        return thisSize;
    }
    
    /**
     * Determine wether the SimpleList is empty.
     */
    bool empty() const{
        return size()==0;
    }
    
    /**
     * Initiate the SimpleList.
     */
    void init(){
        thisSize =0;
        head =new Node;
        tail =new Node;
        head->next =tail;
        tail->next =head;
    }
    
protected:
    /**
     * Inserts a new node at the front of the SimpleList.
     */
    void Insert_Node_Begin(const List & data );
    
    /**
     * Inserts a new node at the back of the SimpleList.
     */
    void Insert_Node_End(const List & data);
    
    /**
     * Remove the node at the front of the SimpleList.
     */
    List Remove_Node_Begin();
};

//subclass: Stack
template <class StackItem>
class Stack : public SimpleList<StackItem>
{
public:
    /**
     * Stack constructor.
     */
    Stack(string name): SimpleList<StackItem>(name) {}
    
    /**
     * This function creates a new Node at the top of stack.
     */
    void push(const StackItem & data ){
        this->Insert_Node_Begin( data  );
    };
    
    /**
     * This function remove the top Node in stack.
     */
    StackItem pop(){
        return this->Remove_Node_Begin();
    };
};


//subclass: Queue
template <class QueueItem>
class Queue: public SimpleList<QueueItem>
{
public:
    /**
     *  Queue constructor.
     */
    Queue(string name): SimpleList<QueueItem>(name) {}
    
    /**
     * This function creates a new Node at the end of queue.
     */
    void push(const QueueItem & data){
        this->Insert_Node_End(data );
    };
    
    /**
     * This function removes the top Node in queue.
     */
    QueueItem pop(){
        return this->Remove_Node_Begin();
    };
};


/**
 * Inserts a new node at the front of the list.
 */
template <class List>
void SimpleList<List>::Insert_Node_Begin(const List & data )
{
    Node* newn = new Node(data);
    if (thisSize>0){
        newn->next = head;
        head = newn;
    }
    else{
        newn->next = NULL;
        head = newn;
        tail = newn;
    }
    thisSize ++;
}

/**
 * Inserts a new node at the back of the List.
 **/
template <class List>
void SimpleList<List>::Insert_Node_End(const List & data ){
    Node* newn = new Node(data);
    if (thisSize>0){
        tail->next = newn; //
        tail = newn;
        tail->next = NULL;
    }
    else{
        newn->next = NULL;
        head = newn;
        tail = newn;
    }
    thisSize ++;
}

/**
 * Removes the node at the back of the List.
 **/
template <class T>
T SimpleList<T>::Remove_Node_Begin(){
    Node *remove=head;
    if (head==tail){
        head=NULL;
        tail=NULL;
    }
    else{
        head=head->next;
    }
    thisSize --;
    return remove->data;
};




