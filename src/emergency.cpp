#include "../include/emergency.h"
#include "../include/user.h"
#include "../include/queue.h"
#include "../include/medicine.h"

#include <iostream>
#include <limits>

int emDoctorCount = 0;

emergencyDoctor::emergencyDoctor() : next(nullptr), queue(nullptr) {}

void printEmDoctor(emergencyDoctor* emDoctorHead) {
    if (emDoctorHead == nullptr) {
        std::cout << "\nNo Emergency Doctor Available\n\n";
        return;
    }
    emergencyDoctor* ptr = emDoctorHead;
    int i = 1;
    while (ptr != nullptr) {
        std::cout << i++ << "." << ptr->docName << std::endl;
        ptr = ptr->next;
    }
}

emergencyDoctor* findEmDoctorInUsers(const user* currentUser, emergencyDoctor* &emergencyDoctorsHead) {
    if (emergencyDoctorsHead == nullptr) {
        std::cout << "\nNo Emergency Doctor Available\n\n";
        return nullptr;
    }

    std::string name = currentUser->firstName + " " + currentUser->lastName;
    emergencyDoctor* docTemp = emergencyDoctorsHead;

    while (docTemp != nullptr) {
        if (name == docTemp->docName)
            return docTemp;
        docTemp = docTemp->next;
    }

    std::cout << "\nEmergency Doctor Not Found\n\n";
    return nullptr;
}

void addEmergencyDoctor(user* &usersHead, emergencyDoctor* &emDoctorsHead) {
    user* temp = newUser(usersHead);
    if (temp == nullptr) {
        std::cout << "Error in user creation.\nReturning to management Menu...\n";
        return;
    }

    emergencyDoctor* newDoctor = new emergencyDoctor;
    newDoctor->queue = new emergencyQueue;
    newDoctor->docName = temp->firstName + " " + temp->lastName;

    newDoctor->next = emDoctorsHead;
    emDoctorsHead = newDoctor;

    std::cout << "\nEmergency Doctor " << newDoctor->docName << " added successfully.\n";
    emDoctorCount++;
}

void assignPatientToEmergency(user* &patient, int priority, emergencyDoctor* &currentDoctor) {
    if (patient == nullptr || currentDoctor == nullptr) {
        std::cout << "\nInvalid patient or doctor information.\n" << std::endl;
        return;
    }
    currentDoctor->queue->enqueue(patient, priority);
    std::cout << "\nPatient " << patient->firstName << " " << patient->lastName
              << " added to emergency queue\n\n";
}

void triage(user* &currentPatient, user* &userHead, emergencyDoctor* &emDoctorHead) {
    if (userHead == nullptr) {
        std::cout << "\nNo users registered yet!\n\n";
        return;
    }
    if (emDoctorCount == 0) {
        std::cout << "\nNo Emergency Doctor Available\n\n";
        return;
    }

    int choice;
    std::cout << "Select The Doctor:\n";
    printEmDoctor(emDoctorHead);
    std::cin >> choice;

    if (choice < 1 || choice > emDoctorCount) {
        std::cout << "Invalid choice.\n";
        return;
    }

    emergencyDoctor* currentDoctor = emDoctorHead;
    for (int i = 0; i < choice - 1; i++)
        currentDoctor = currentDoctor->next;

    std::string ID;
    std::cout << "Enter Patient's ID:";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, ID);

    user* check = searchPatientID(userHead, ID);
    if (check == nullptr)
        currentPatient = newUser(userHead);
    else
        currentPatient = check;

    int prio;
    std::cout << "Enter Priority Code:";
    std::cin >> prio;

    assignPatientToEmergency(currentPatient, prio, currentDoctor);
}

void emDoctor(user* &currentUser, emergencyDoctor* &emergencyDoctorsHead) {
    char command = '\0';

    emergencyDoctor* currentDoc = findEmDoctorInUsers(currentUser, emergencyDoctorsHead);
    if (currentDoc == nullptr) {
        std::cout << "\nSomething Went Wrong\n\n";
        return;
    }

    while (true) {
        std::cout << "\n[0]: Return To The Main Page\n"
                  << "[1]: Emergency Patients List\n"
                  << "[2]: Start Emergency Visit\n";
        std::cin >> command;

        if (command == '0') break;

        if (command == '1') {
            currentDoc->queue->printQueue();
        }
        else if (command == '2') {
            if (currentDoc->queue->isEmpty()) {
                std::cout << "\nNo Patient To Visit\n\n";
                continue;
            }

            user* patient = currentDoc->queue->head->patient;
            std::cout << "Patient's name: " << patient->firstName << " " << patient->lastName
                      << " -- Age: " << patient->age << std::endl;

            char need = '\0';
            std::cout << "\nDoes the patient need medicine? [y/n]:\n";
            std::cin >> need;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (need == 'y' || need == 'Y') {
                int medCount = 0;
                std::cout << "\nHow many medicines does the patient need?";
                std::cin >> medCount;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::string temp;
                for (int i = 0; i < medCount; i++) {
                    std::cout << "Medicine " << i + 1 << ":";
                    std::cin >> temp;
                    patient->med->push(temp);
                }
                std::cout << "DONE!\n";
                currentDoc->queue->dequeue();
            }
            else if (need == 'n' || need == 'N') {
                std::cout << "DONE!" << std::endl;
                currentDoc->queue->dequeue();
            }
            else
                std::cout << "\nInvalid input!!\n";
        }
    }
}