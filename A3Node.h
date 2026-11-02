#ifndef A3NODE_H
#define A3NODE_H

#include <iostream>

struct Node {
    std::string url; 
    Node* next;
    Node* prev;

    Node() {
        url = "";
        next = prev = nullptr;
    }
    Node(std::string url, Node* next, Node* prev){
        this->url = url;
        this->next = next;
        this->prev = prev; 
    }
};

#endif