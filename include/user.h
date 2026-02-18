#ifndef USER_H
#define USER_H

#include <iostream>

class medicine;

class user {
public:
    std::string firstName, lastName, ID, userName, password;
    int age;
    char role;
    // roles:
    // management: '1' , clinic doctor: '2' , emergency doctor: '3'
    // patient: '4' , pharmacy: '5' , triage: '6'

    user *next;
    medicine *med;

    user();
    ~user();
};

user *newUser(user *&first);
user *login(user *&first);
user *search(user *first);
user *exists(user *first, std::string username, std::string password);
user *searchPatientID(user* userHead, std::string ID);
void printUser(const user *first);
void printAllUsers(user *first);
void deleteUser(user *&usersHead);
bool isUsernameTaken(user *userHead, std::string userName);

#endif
