#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>

class visitQueue;
class user;
class clinic;

class doctor {
    public:
        std::string docName;
        visitQueue *queue;

        doctor *next;

        doctor();


};

// Since the list of doctors is only used within the clinics list, we cannot directly access a doctor's information.
// Therefore, we must search for the corresponding doctor in the users list.
doctor* findDoctorInUsers(const user* currentUser, clinic* clinicHead);
void addDrToClinic(clinic *&first1, user *&first2);
void Doctor(user *&currentUser, clinic *&clinicHead);

#endif
