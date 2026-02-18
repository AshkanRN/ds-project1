#include "../include/user.h"
#include "../include/utils.h"
#include "../include/medicine.h"

#include <iostream>
#include <limits>

using namespace std;

user::user() {
    next = nullptr;
    med = nullptr;
}

user::~user() {
    delete med;
}


bool isUsernameTaken(user* userHead, std::string userName){

    user* ptr = userHead;
    while (ptr != nullptr) {
        if (ptr->userName == userName)
            return true;

        ptr = ptr->next;
    }
    return false;
}


user* exists(user* first,string username , string password) {

    user* ptr = first , * temp = nullptr;

    while (ptr != nullptr) {
        if (username == ptr->userName && password == ptr->password) {
            temp = ptr;
            break;
        }
        ptr = ptr->next;
    }
    return temp;

}


user* login(user* &first) {

    if (first == nullptr) {
        cout<<"\nNo users registered yet!! SIGN UP first\n\n";
        return nullptr;
    }
    string username , password;

    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    cout<<"Username:";
    getline(cin,username);
    username = toLowerCase(username);

    cout<<"Password:";
    getline(cin,password);

    // cin.ignore(numeric_limits<streamsize>::max(),'\n');

    user * check = exists(first,username,password);
    if ( check != nullptr)
        return check;

    else {
        cout<<"\nUser Not Found !!\n";
        return nullptr;
    }

}

user* search(user* first) {
    if (first == nullptr) {
        cout<<"There Is no user yet !!"<<endl;
        return nullptr;
    }
    string ID;
    cout<<"Enter ID to Search:";
    getline(cin>>ws,ID);

    user* temp = first;
    while (temp != nullptr) {
        if (ID == temp->ID)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

user* newUser(user* &first) {

    user* newNode = new user;

    cout<<" <  Sign-Up  > "<<endl;

    cout<<"Username:";
    getline(cin>>ws,newNode->userName);
    newNode->userName = toLowerCase(newNode->userName);


    if (isUsernameTaken(first, newNode->userName)) {
        cout<<"\nThis Username is already taken !!\nReturning to the Menu...\n";
        delete newNode;
        return nullptr;
    }

    cout<<"Password:";
    getline(cin,newNode->password);

    cout<<"First Name:";
    getline(cin,newNode->firstName);
    newNode->firstName = toLowerCase(newNode->firstName);

    cout<<"Last Name:";
    getline(cin,newNode->lastName);
    newNode->lastName = toLowerCase(newNode->lastName);

    cout<<"ID:";
    getline(cin,newNode->ID);

    string ageStr;
    cout<<"Age:";

    getline(cin,ageStr);

    try{
        newNode->age = stoi(ageStr);
    }
    catch (invalid_argument& e) {
        cout << "Invalid Input for 'Age'. Please enter a valid integer: ";
        delete newNode;
        return nullptr;
    }
    catch (out_of_range& e) {
        cout << "Input is out of integer range (age). Try again: ";
        delete newNode;
        return nullptr;
    }

    cout<<"\nSelect Role:"
          "\n[1] management"
          "\n[2] clinic doctor"
          "\n[3] emergency doctor"
          "\n[4] patient"
          "\n[5] pharmacy"
          "\n[6] triage"
          "\n--> ";
    int role;
    cin>>role;

    if (role <= 0 || role > 6 ){
        cout<<"\nInvalid !, Returning to Main Menu\n";
        delete newNode;
        return nullptr;
    }

    newNode->role = role + '0';

    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    if (newNode->role == '4')
        newNode->med = new medicine();

    if (first == nullptr)
        first = newNode;

    else {
        newNode->next = first;
        first = newNode;
    }
    return newNode;

}



void printUser(const user* first) { // print content of one node (in user Linked list)
    if (first == nullptr) {
        cout<<"\nNo users registered yet! \n"<<endl;
        return;
    }

    cout<<"First Name:"<<first->firstName<<" -- "
        <<"Last Name:"<<first->lastName<<" -- "
        <<"Age:"<<first->age<<" -- "
        <<"ID:"<<first->ID<<" -- "
        <<"User Name:"<<first->userName<<" -- "
        <<"Role:";

    switch (first->role) {
        case '1' : cout<<"Management\n"; break;
        case '2' : cout<<"Clinic Doctor\n"; break;
        case '3' : cout<<"Emergency Doctor\n"; break;
        case '4' : cout<<"Patient\n"; break;
        case '5' : cout<<"Pharmacy\n"; break;
        case '6' : cout<<"Triage\n"; break;
        default: cout<<"invalid\n"; break;
    }

}

void printAllUsers(user* first){ // print content of All nodes (in user Linked list)
    if (first == nullptr) {
        cout<<"No users registered yet!"<<endl;
        return;
    }
    user* ptr = first;

    int i = 1;
    cout<<endl;
    while (ptr != nullptr) {
        cout<<i++<<".";
        printUser(ptr);
        ptr = ptr->next;
    }

}

void deleteUser(user* &usersHead) {
    if (usersHead == nullptr) {
        cout<<"\nNo users registered yet!\n\n";
        return;
    }
    string username,password;

    cout<<"Username:";
    getline(cin>>ws,username);

    cout<<"Password:";
    getline(cin>>ws,password);

    user* ptr = usersHead;
    user* prev = nullptr;

    while (ptr != nullptr) {
        if (ptr->password == password && ptr->userName == username)
            break;
        prev = ptr;
        ptr = ptr->next;
    }

    if (ptr == nullptr) {
        cout<<"\nUser Not Found !!\n\n";
        return;
    }

    if (ptr == usersHead) {
        usersHead = usersHead->next;
        delete ptr;
    }

    else{
        prev->next = ptr->next;
        ptr->next = nullptr;
        delete ptr;
    }

}

user* searchPatientID(user* userHead,string ID) {
    if (userHead == nullptr)
        return nullptr;
    user* ptr = userHead;

    while (ptr != nullptr) {
        if (ptr->ID == ID && ptr->role == '4')
            return ptr;
        ptr = ptr->next;
    }
    return nullptr;
}