#ifndef CLINIC_H
#define CLINIC_H

#include <iostream>

extern int clinicCount;

class doctor;

class clinic {
    public:
        std::string clinicName;
        doctor *head = nullptr;
        int doctorsCount = 0;

        clinic *next;

        clinic();
        ~clinic();
};


void addClinic(clinic *&first);
void printClinics(clinic *first);
void printDoctors(const clinic *clinicPtr);


#endif