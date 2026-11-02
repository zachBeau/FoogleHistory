

#include <cassert>
#include "A3List.h"

#ifndef NDEBUG
    #define DEBUG_LOG(msg) std::cerr << "[debug] " << msg << '\n'
#else
    #define DEBUG_LOG(msg) ((void)0)
#endif


FoogleHistory::FoogleHistory() {
    DEBUG_LOG("FoogleHistory default constructor called");
    front = rear = page = nullptr;     
}

void FoogleHistory::visit(const std::string& url) {
    DEBUG_LOG("FoogleHistory::vist called");
    //empty list, create first page
    if (historyEmpty()) {
        DEBUG_LOG("FoogleHistory::visit history empty");
        front = rear = page = new Node(); 
        page->url = url; 
        return; 
    }

    //non-empty list, delete everything after page
    DEBUG_LOG("FoogleHistory::vist deleting forward history");
    front = page; 
    Node* futureList = page->next;
    while (futureList != nullptr) {
        Node* current = futureList;
        futureList = futureList->next;
        delete current; 
    }
    //create new node, assign to front
    DEBUG_LOG("FoogleHistory::visit create new node, front = new node");
    Node* newURL = new Node(url, nullptr, front);
    front->next = newURL;
    front = newURL; 
    page = newURL; 
   
}

bool FoogleHistory::back() {
    DEBUG_LOG("FoogleHistory::back called");
    if (historyEmpty() || page->prev == nullptr) {
        DEBUG_LOG("FoogleHistory::back, list is empty or no previous history, return false");
        std::cout << "Empty list or no previous history" << std::endl; 
        return false;
    }
    page = page->prev;
    DEBUG_LOG("FoogleHistory::back, Moving back, returning true");
    return true; 
}

bool FoogleHistory::forward() {
    DEBUG_LOG("FoogleHistory::forward() called");
    if (historyEmpty() || page->next == nullptr) {
        DEBUG_LOG("FoogleHistory::forward, list is empty or no forward history, returning false");
        std::cout << "Empty list or no forward history" << std::endl; 
        return false;
    }
    page = page->next;
    DEBUG_LOG("FoogleHistory::forward, moving forward, returning true");
    return true; 
}

void FoogleHistory::showHistory() const {
    DEBUG_LOG("FoogleHistory::showHistory called");
    if (historyEmpty()) {
        DEBUG_LOG("FoogleHistory::showHistory empty check true, list is empty");
        std::cout << "List is empty" << std::endl; 
        return; 
    }
    std::cout << "DISPLAYING HISTORY: " << std::endl; 
    Node* current = page;
    std::cout << "Current page: " << page->url << std::endl;  
    while (current != nullptr) {
        current = current->prev; 
        if (current == nullptr) {
            std::cout << "Previous Page: History is empty" << std::endl;
            return; 
        }
        std::cout << "Previous Page: " << current->url << std::endl;  
    }
}

void FoogleHistory::deleteHistory(size_t start, size_t end) {
    DEBUG_LOG("FoogleHistory::deleteHistory called");
    DEBUG_LOG("Check for empty list");
    if (historyEmpty()) {
        std::cout << "List is empty, nothing to delete" << std::endl;
        return;
    }
    //1. check range
    DEBUG_LOG("Validate Range"); 
    size_t count = 0;
    for (Node* range = rear; range != nullptr; range = range->next) {
        count++; 
    }
    if (start > end || end >= count) {
        std::cout << "Invalid delete range" << std::endl; 
        return; 
    }

    //2. find first node and last node
    Node* first = rear; 
    for (size_t i = 0; i < start; i++) {
        first = first->next; 
        DEBUG_LOG("First = rear loop");
    }
    Node* last = first; 
    for (size_t i = start; i < end; i++) {
        last = last->next; 
        DEBUG_LOG("last = first loop");
    }
    //3. save the nodes on either side of first and last
    Node* before = first->prev; //node before delete range 
    Node* after = last->next;  //node after delete range
    //4. delete the range -- check for current
    bool pageDeleted = false;
    Node* current = first; 
    DEBUG_LOG("Deleting forward history");
    while (current != after) {
        Node* temp = current->next;
        if (current == page) {
            pageDeleted = true;
        } 
        delete current;
        current = temp; 
    }

    //5. attach the surving ends checking for nullptr
    DEBUG_LOG("Ataching new ends");
    if (before != nullptr) {
        before->next = after; 
    } else {
        DEBUG_LOG("Before = nullptr");
        rear = nullptr; 
    }
        rear = after; 
    if (after != nullptr) {
        after->prev = before; 
    } else {
        DEBUG_LOG("after == nullptr");
        front = nullptr;
    }
    //6. reassign front if necessary
    if (pageDeleted) {
        DEBUG_LOG("Current page was deleted, reassigning current page");
        page = (before != nullptr) ? before : after;
    } 
    while (front != nullptr) {
        if (front->next == nullptr) {
            DEBUG_LOG("front->next == nullptr");
            return;
        }
        DEBUG_LOG("Moving front to end of list"); 
        front = front->next; 
    } 
    while (rear != nullptr) {
        if (rear->prev == nullptr) {
            DEBUG_LOG("rear->prev == nullptr");
            return; 
        }
        rear = rear->prev; 
    }
}

void FoogleHistory::showCurrentPage() const {
    DEBUG_LOG("FoogleHistory::showCurrentPage() called");
    if (historyEmpty()) {
        DEBUG_LOG("No current page");
        std::cout << "Empty list, no current page" << std::endl; 
        return; 
    }
    std::cout << "Current Page: " << page->url << std::endl; 
}

void FoogleHistory::enqueueVisit(const std::string url) {
    DEBUG_LOG("FoogleHistory::enqueueVisit called");
    pending.push(url); 
}

bool FoogleHistory::processNextRequest() {
    DEBUG_LOG("FoogleHistory::processNextRequest() called");
    Node* nextURL = pending.popRear(); 
    if (nextURL == nullptr) {
        DEBUG_LOG("FoogleHistory::processNextRequest() FutureList is empty, return false");
        return false; 
    } else {
        DEBUG_LOG("Future list is not empty");
        front->next = nextURL;
        nextURL->prev = front; 
        front = front->next; 
        page = nextURL; 
    }
    return true; 
}

void FoogleHistory::showPendingRequest() {
    DEBUG_LOG("FoogleHistory::showPendingRequest called");
    pending.dislpayList(); 
}

bool FoogleHistory::historyEmpty() const {
    DEBUG_LOG("FoogleHistory::historyEmpty called");
    //using assert to check for dangling pointers/memory leaks
    //check if both are null or both are non-nullptr.
    assert((front == nullptr) == (rear == nullptr)); 
    //assert (front == nullptr && rear == nullptr); aborts if there is anything in the list
    DEBUG_LOG("checking for empty history");
    return (front == nullptr); 
}

void FoogleHistory::showAll() const {
    DEBUG_LOG("FoogleHistory::showAll called");
    if(historyEmpty()) {
        DEBUG_LOG("showAll() history is empty");
        std::cout << "All history is empty" << std::endl; 
        return; 
    }
    
    Node* temp = front;
    while (temp) {
        std::cout << temp->url << std::endl;
        temp = temp->prev; 
    }
}
