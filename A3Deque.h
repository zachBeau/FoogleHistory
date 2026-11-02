#ifndef A3DEQUE_H
#define A3DEQUE_H

#include "A3Node.h"

struct FutureList {
    Node* futureFront;
    Node* futureRear; 

    FutureList();
    void push(std::string);    
    Node* popRear();    
    void dislpayList();
 

};


#endif