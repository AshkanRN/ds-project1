#include "../include/clinic.h"
#include "../include/user.h"
#include "../include/queue.h"
#include "../include/doctor.h"

#include <iostream>
#include <limits>

int clinicCount = 0;

clinic::clinic() : next(nullptr), head(nullptr), doctorsCount(0) {}

clinic::~clinic() {
    doctor* curr = head;
    while (curr != nullptr) {
        doctor* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

//doctor::doctor() : next(nullptr), queue(nullptr) {}

void printClinics(clinic* first) {
    if (first == nullptr) {
        std::cout << "No Clinic added yet" << std::endl;
        return;
    }
    clinic* ptr = first;
    int i = 1;
    while (ptr != nullptr) {
        std::cout << i++ << "." << ptr->clinicName << std::endl;
        ptr = ptr->next;
    }
}

void printDoctors(const clinic* clinicPtr) {
    if (clinicPtr == nullptr) {
        std::cout << "\nThere is No clinic\n\n";
        return;
    }
    doctor* temp = clinicPtr->head;
    if (temp == nullptr) {
        std::cout << "\nThere is No Doctor\n\n";
        return;
    }
    int i = 1;
    while (temp != nullptr) {
        std::cout << i++ << "." << temp->docName << std::endl;
        temp = temp->next;
    }
}

void addClinic(clinic* &first) {
    clinic* newClinic = new clinic;
    std::cout << "Clinic Name:";
    std::getline(std::cin >> std::ws, newClinic->clinicName);

    if (first == nullptr)
        first = newClinic;
    else {
        newClinic->next = first;
        first = newClinic;
    }
    clinicCount++;
}

void addDrToClinic(clinic* &first1, user* &first2) {
    if (first1 == nullptr) {
        std::cout << "\nNo clinics have been added yet!\n\n";
        return;
    }

    user* temp = newUser(first2);
    if (temp == nullptr)
        return;

    doctor* newDoctor = new doctor;
    newDoctor->queue = new visitQueue;
    newDoctor->docName = temp->firstName + " " + temp->lastName;

    std::cout << "Add to which Clinic?" << std::endl;
    printClinics(first1);

    clinic* ptr = first1;
    int command;
    std::cin >> command;

    if (command < 1 || command > clinicCount) {
        std::cout << "Invalid clinic choice.\n";
        delete newDoctor;
        return;
    }

    for (int i = 0; i < command - 1; i++)
        ptr = ptr->next;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (ptr->head == nullptr)
        ptr->head = newDoctor;
    else {
        newDoctor->next = ptr->head;
        ptr->head = newDoctor;
    }
    ptr->doctorsCount++;
}

doctor* findDoctorInUsers(const user* currentUser, clinic* clinicHead) {
    if (clinicHead == nullptr) {
        std::cout << "\nNo Clinics Available\n\n";
        return nullptr;
    }

    std::string name = currentUser->firstName + " " + currentUser->lastName;
    clinic* clinicTemp = clinicHead;

    while (clinicTemp != nullptr) {
        doctor* doctorTemp = clinicTemp->head;
        while (doctorTemp != nullptr) {
            if (name == doctorTemp->docName)
                return doctorTemp;
            doctorTemp = doctorTemp->next;
        }
        clinicTemp = clinicTemp->next;
    }

    std::cout << "\nDoctor Not Found\n\n";
    return nullptr;
}