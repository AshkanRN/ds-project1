#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

class user;


class visitQueue {
public:
    struct node {
        user* patient;

        node* next;
        node();
    };

    node* front , *rear;

    visitQueue();
    ~visitQueue();

    bool isEmpty() const;
    void enqueue(user* newPatient);
    void dequeue();
    void printQueue() const;
    void deleteFromQueue(user* &target);
};


class emergencyQueue {
    public:
        struct node {
            user* patient;
            int priority;

            node* next;

            node();
        };

        node* head;

        emergencyQueue();
        ~emergencyQueue();

        bool isEmpty() const;
        void enqueue(user* patient,int priority);
        void dequeue();
        void printQueue() const;
};

#endif
