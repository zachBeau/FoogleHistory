#include <cassert> 
#include "A3Deque.h"



#ifndef NDEBUG
    #define DEBUG_LOG(msg) std::cerr << "[debug] " << msg << '\n'
#else
    #define DEBUG_LOG(msg) ((void)0)
#endif



FutureList::FutureList() {
    DEBUG_LOG("FutureList default constructor called");
    futureFront = futureRear = nullptr; 
}

void FutureList::push(std::string url) {
    DEBUG_LOG("FutureList::push(string) called");
    if (futureFront == nullptr && futureRear == nullptr) {
        DEBUG_LOG("Empty list, create first node");
        futureFront = futureRear = new Node();
        futureFront->url = url;
        return; 
    }
    DEBUG_LOG("Create next future page");
    Node* futurePage = new Node(url, nullptr, futureFront);
    futureFront->next = futurePage;
    futureFront = futurePage; 
}

Node* FutureList::popRear() {
    DEBUG_LOG("FutureList::popRear() called");
    if (futureRear == nullptr) {
        DEBUG_LOG("FutureList rear is nullptr, list is empty");
        std::cout << "List is empty " << std::endl; 
        return nullptr;
    }
    //create new pointer to FutureRear
    Node* listTransfer = futureRear; 

    //assign new futureRear make new futureRear->prev point to nullptr
    
    futureRear = futureRear->next; 
    if(futureRear != nullptr) {
        futureRear->prev = nullptr;
    } else futureFront = nullptr; 
    
    //detach Futurerear pointer
    listTransfer->next = nullptr;
    listTransfer->prev = nullptr; 
    //return new pointer
    return listTransfer; 
}

void FutureList::dislpayList() {
    DEBUG_LOG("FutureList::displayList() called");
    std::cout << "Pending Requeusts: " << std::endl; 
    if (futureFront == nullptr) {
        DEBUG_LOG("FutureList is empty");
        std::cout << "List is empty" << std::endl; 
    }
    Node* current = futureRear;     
    while (current != nullptr) {
        DEBUG_LOG("Printing Future List");
        std::cout << "Next URL: " << current->url << std::endl; 
        current = current->next; 
    }
}
