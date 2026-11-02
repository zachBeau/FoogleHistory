#ifndef A3LIST_H
#define A3LIST_H

#include <cassert> 
#include <iostream>
#include <string>
#include "A3Node.h"
#include "A3Deque.h"

class FoogleHistory {  //like google only foogle because its fake ;)
    Node* front;
    Node* rear;
    Node* page; 
    FutureList pending; 
public:     
    //default construcotr
    FoogleHistory(); 
    //visit
    void visit(const std::string&);
    //back
    bool back();
    //forward
    bool forward(); 
    //display history
    void showHistory() const;
    //delete range
    void deleteHistory(size_t, size_t); //size_t depends on target platform, testing performed on windows, size_t = unsigned long long
    //current page
    void showCurrentPage() const; 
    
    //for deque behavior
    //enqueue visit    
    void enqueueVisit(const std::string);
    //process next visit
    bool processNextRequest();
    //display pending requests;
    void showPendingRequest(); 

    //added functions
    bool historyEmpty() const;

    void showAll() const; 
};

#endif