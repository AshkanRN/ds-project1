#include "../include/medicine.h"
#include <iostream>
#include <limits>

medicine::node::node() : next(nullptr) {}

medicine::medicine() : top(nullptr) {}

medicine::~medicine() {
    while (top != nullptr) {
        node* temp = top;
        top = top->next;
        delete temp;
    }
}

bool medicine::isEmpty() const {
    return top == nullptr;
}

void medicine::push(const std::string& medName) {
    node* newNode = new node;
    newNode->medicineName = medName;
    newNode->next = top;
    top = newNode;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string medicine::pop() {
    if (isEmpty()) {
        std::cout << "Stack is Empty !!" << std::endl;
        return "";
    }
    node* temp = top;
    std::string medName = temp->medicineName;
    top = top->next;
    delete temp;
    return medName;
}

void medicine::printMedicine() const {
    node* temp = top;
    while (temp != nullptr) {
        std::cout << temp->medicineName << std::endl;
        temp = temp->next;
    }
}