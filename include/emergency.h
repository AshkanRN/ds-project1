#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <iostream>

extern int emDoctorCount;

class emergencyQueue;
class user;

class emergencyDoctor {
    public:
        std::string docName;
        emergencyQueue *queue;

        emergencyDoctor *next;

        emergencyDoctor();
};


void printEmDoctor(emergencyDoctor *emDoctorHead);
void addEmergencyDoctor(user *&usersHead, emergencyDoctor *&emDoctorsHead);
void assignPatientToEmergency(user *&patient, int priority, emergencyDoctor *&currentDoctor);
void triage(user * &currentPatient, user *&userHead, emergencyDoctor *&emDoctorHead);
void emDoctor(user *&currentUser, emergencyDoctor *&emergencyDoctorsHead);
emergencyDoctor *findEmDoctorInUsers(const user *currentUser, emergencyDoctor *&emergencyDoctorsHead);

#endif
