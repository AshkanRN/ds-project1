#include "../include/doctor.h"
#include "../include/clinic.h"
#include "../include/user.h"
#include "../include/queue.h"
#include "../include/medicine.h"

#include <iostream>
#include <limits>

doctor::doctor() : next(nullptr), queue(nullptr) {}

void Doctor(user* &currentUser, clinic* &clinicHead) {
    if (clinicHead == nullptr) {
        std::cout << "\nNo Clinics Available\n\n";
        return;
    }

    char command = '\0';
    doctor* currentDoc = findDoctorInUsers(currentUser, clinicHead);

    if (currentDoc == nullptr) {
        std::cout << "\nSomething Went Wrong\n\n";
        return;
    }

    while (true) {
        std::cout << "\n[0]: Return To The Main Page\n"
                  << "[1]: Patients List\n"
                  << "[2]: Visit\n";
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

            user* patient = currentDoc->queue->front->patient;
            char need = '\0';
            std::cout << "Patient's name: " << patient->firstName << " " << patient->lastName
                      << " -- age: " << patient->age;
            std::cout << "\nNeeds Medicine? [y/n]:\n";
            std::cin >> need;

            if (need == 'y' || need == 'Y') {
                int medCount = 0;
                std::cout << "\nHow many medicines does The Patient needs?";
                std::cin >> medCount;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::string temp;
                for (int i = 0; i < medCount; i++) {
                    std::cout << "Medicine " << i + 1 << ":";
                    std::cin >> temp;
                    patient->med->push(temp);
                }
                std::cout << "DONE !\n";
                currentDoc->queue->dequeue();
            }
            else if (need == 'n' || need == 'N') {
                std::cout << "DONE !" << std::endl;
                currentDoc->queue->dequeue();
            }
            else
                std::cout << "\nInvalid !!\n";
        }
    }
}