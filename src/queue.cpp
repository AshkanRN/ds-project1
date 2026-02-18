#include "../include/queue.h"
#include "../include/user.h"
#include <iostream>

// visitQueue::node
visitQueue::node::node() : next(nullptr), patient(nullptr) {}

// visitQueue
visitQueue::visitQueue() : front(nullptr), rear(nullptr) {}

visitQueue::~visitQueue() {
    while (!isEmpty())
        dequeue();
}

bool visitQueue::isEmpty() const {
    return front == nullptr;
}

void visitQueue::enqueue(user* newPatient) {
    node* newNode = new node;
    newNode->patient = newPatient;

    if (isEmpty())
        rear = front = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

void visitQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "\nThe Queue Is Empty\n" << std::endl;
        return;
    }
    node* temp = front;
    front = front->next;
    delete temp;

    if (front == nullptr)
        rear = nullptr;
}

void visitQueue::printQueue() const {
    if (isEmpty()) {
        std::cout << "\nThere is NO Patient in The Queue !!\n\n";
        return;
    }
    node* ptr = front;
    int position = 1;
    std::cout << std::endl;
    while (ptr != nullptr) {
        std::cout << position++ << ".  " << ptr->patient->firstName << "  " << ptr->patient->lastName
                  << " -- ID:" << ptr->patient->ID << " -- Age:" << ptr->patient->age << std::endl;
        ptr = ptr->next;
    }
    std::cout << std::endl;
}

void visitQueue::deleteFromQueue(user* &target) {
    if (front == nullptr) {
        std::cout << "\nThe Queue Is EMPTY !!\n\n";
        return;
    }

    if (front->patient == target) {
        dequeue();
        return;
    }

    node* ptr = front;
    while (ptr->next != nullptr) {
        if (ptr->next->patient == target)
            break;
        ptr = ptr->next;
    }

    if (ptr->next == nullptr) {
        std::cout << "Patient not found in the queue.\n";
        return;
    }

    node* temp = ptr->next;
    ptr->next = temp->next;

    if (temp == rear)
        rear = ptr;

    delete temp;
}


// emergencyQueue::node
emergencyQueue::node::node() : next(nullptr), priority(0), patient(nullptr) {}

// emergencyQueue
emergencyQueue::emergencyQueue() : head(nullptr) {}

emergencyQueue::~emergencyQueue() {
    while (!isEmpty())
        dequeue();
}

bool emergencyQueue::isEmpty() const {
    return head == nullptr;
}

void emergencyQueue::enqueue(user* patient, int priority) {
    node* newNode = new node;
    newNode->patient = patient;
    newNode->priority = priority;

    if (isEmpty() || priority < head->priority) {
        newNode->next = head;
        head = newNode;
    } else {
        node* current = head;
        while (current->next != nullptr && current->next->priority <= priority)
            current = current->next;
        newNode->next = current->next;
        current->next = newNode;
    }
}

void emergencyQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "\nThe Queue Is Empty\n\n";
        return;
    }
    node* temp = head;
    head = head->next;
    delete temp;
}

void emergencyQueue::printQueue() const {
    if (isEmpty()) {
        std::cout << "\nThere is NO Patient in The Queue !!\n\n";
        return;
    }
    node* current = head;
    int position = 1;
    std::cout << std::endl;
    while (current != nullptr) {
        std::cout << position++ << ".  " << current->patient->firstName << "  " << current->patient->lastName
                  << " -- ID:" << current->patient->ID << " -- Age:" << current->patient->age << std::endl;
        current = current->next;
    }
    std::cout << std::endl;
}