#ifndef MEDICINE_H
#define MEDICINE_H

#include <iostream>

class medicine {
    public:
        struct node {
            std::string medicineName;
            node* next;
            node();
        };

        node* top;

        medicine();
        ~medicine();

        bool isEmpty() const;
        void push(const std::string &medName);
        void printMedicine() const;
        std::string pop();
};

#endif
