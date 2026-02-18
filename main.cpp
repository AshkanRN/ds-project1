#include "include/user.h"
#include "include/clinic.h"
#include "include/doctor.h"
#include "include/emergency.h"
#include "include/medicine.h"
#include "include/queue.h"
#include "include/utils.h"

#include <iostream>
#include <limits>

using namespace std;


void patient(user* &currentUser,clinic* &clinicHead,emergencyDoctor* &emDoctorHead,user* &userHead) {
    char command = '\0';
    clinic* selectedClinic = nullptr;
    doctor* selectedDoctor = nullptr;
    while (true) {
        if (selectedClinic != nullptr && selectedDoctor != nullptr) {
            cout<<"User: "<<currentUser->userName<<endl
                <<"Selected Clinic: "<<selectedClinic->clinicName<<endl
                <<"Selected Doctor: "<<selectedDoctor->docName<<endl;
        }
        cout<<"[0]: Return to The Main Page\n"
            <<"[1]: Make an Appointment\n"
            <<"[2]: Cancel The Appointment\n"
            <<"[3]: Emergency\n";
        cin >> command;


        if (command == '0')
            return;

        if (command == '1') {
            if (clinicHead == nullptr) {
                cout<<"\nNo clinics have been added yet \n\n";
                continue;
            }
            int clinicChoice;

            cout<<"Select a clinic:\n";
            printClinics(clinicHead);
            cin>>clinicChoice;

            if (clinicChoice < 1 || clinicChoice > clinicCount) {
                cout << "Invalid clinic choice. Please try again.\n";
                continue;
            }

            selectedClinic = clinicHead;
            for (int i = 1; i < clinicChoice; i++) {
                selectedClinic = selectedClinic->next;
            }

            int doctorChoice;
            if (selectedClinic->head == nullptr) {
                cout<<"\nThere Is no Doctor in "<<selectedClinic->clinicName<<"\n\n";
                continue;
            }
            cout<<"Select a Doctor in "<<selectedClinic->clinicName<<endl;
            printDoctors(selectedClinic);
            cin>>doctorChoice;

            if (doctorChoice < 1 || doctorChoice > selectedClinic->doctorsCount) {
                cout << "Invalid. Please try again.\n";
                continue;
            }

            selectedDoctor = selectedClinic->head;
            for (int i = 1; i < doctorChoice; i++) {
                selectedDoctor = selectedDoctor->next;
            }
            selectedDoctor->queue->enqueue(currentUser);
        }


        else if (command == '2') {
            if (selectedDoctor == nullptr) {
                cout<<"\nNo Doctor Selected, please Select a Doctor First\n"<<endl;
                continue;
            }
            selectedDoctor->queue->deleteFromQueue(currentUser);

            selectedDoctor = nullptr;
            selectedClinic = nullptr;

            cout << "\nAppointment Canceled.\n\n";
        }


        else if (command == '3') {
            cout<<"\n  <   Triage  >  \n";
            triage(currentUser,userHead,emDoctorHead);
        }
    }

}


void pharmacy(user* usersHead) {
    if (usersHead == nullptr) {
        cout<<"\nNo Patient Available\n\n";
        return;
    }
    user* currentPatient = nullptr;

    char choice = '\0';

    while (true) {
        if (currentPatient != nullptr)
            cout<<"Patient: "<<currentPatient->firstName<<" "<<currentPatient->lastName<<endl;

        cout<<"[0]: Return To main Page\n"
            <<"[1]: Select Patient\n"
            <<"[2]: Medicine List\n"
            <<"[3]: Start Medicine Dispensing\n";
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == '0')
            break;

        else if (choice == '1') {
            string ID;
            cout<<"\nEnter ID:";

            // cin.ignore(numeric_limits<streamsize>::max(),'\n');
            getline(cin,ID);

            user* temp = searchPatientID(usersHead,ID);

            currentPatient = (temp != nullptr) ? temp : currentPatient;
        }

        else if (choice == '2') {

            if (currentPatient == nullptr) {
                cout<<"\nSelect Patient First !!\n\n";
                continue;
            }

            if (currentPatient->med->isEmpty()) {
                cout<<"No medicines have been registered yet !! \n\n";
                continue;
            }

            cout<<currentPatient->lastName<<" Medicine List:\n";
            currentPatient->med->printMedicine();
        }

        else if (choice == '3') {
            if (currentPatient == nullptr) {
                cout<<"\nSelect Patient First !!\n\n";
                continue;
            }
            if (currentPatient->med->isEmpty()) {
                cout<<"medicines has not been registered yet !! \n\n";
                continue;
            }

            while (!currentPatient->med->isEmpty()) {
                char confirm = '\0';
                cout<<"Medicine Name: "<<currentPatient->med->top->medicineName<<endl;

                cout<<"Confirm Medicine? [y/n]:";
                cin>>confirm;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (confirm == 'y' || confirm == 'Y') {
                    cout<<endl<<currentPatient->med->top->medicineName<<" CONFIRMED\n";
                    currentPatient->med->pop();
                }

                else if (confirm == 'n' || confirm == 'N') {
                    cout<<endl<<currentPatient->med->top->medicineName<<" NOT CONFIRMED !!!\n";
                    currentPatient->med->pop();
                }

                else
                    cout<<"\nInvalid !\n\n";

            }

        }

    }

}


void management(user* &usersHead,clinic* &clinicsHead,emergencyDoctor* &emDoctorHead) {
    char command = '\0';

    while (true) {
        cout<<"\n[0]: Return to Main Page"<<endl
            <<"[1]: Sign-up New User"<<endl
            <<"[2]: Delete a User"<<endl
            <<"[3]: Search (based on ID)"<<endl
            <<"[4]: Add Clinic"<<endl
            <<"[5]: Add Doctor"<<endl
            <<"[6]: Add Emergency Doctor"<<endl
            <<"[7]: print All User"<<endl;
        cin>>command;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        if (command == '0')
            break;


        if (command == '1') {
            newUser(usersHead);
        }

        else if (command == '2') {
            deleteUser(usersHead);
        }

        else if (command == '3') {
            user* temp = search(usersHead);
            if (temp == nullptr) {
                cout<<"\nUser Not Found\n\n";
                continue;
            }
            printUser(temp);
        }

        else if (command == '4') {
            addClinic(clinicsHead);
        }

        else if (command == '5') {
            addDrToClinic(clinicsHead,usersHead);
        }

        else if (command == '6') {
            addEmergencyDoctor(usersHead,emDoctorHead);
        }

        else if (command == '7') {
            printAllUsers(usersHead);
            // cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
}



void userActions(user* &currentUser,user* &userHead,clinic* &clinicHead ,emergencyDoctor* &emDoctorHead) {
    if (currentUser == nullptr) {
        cout<<"\nLOG IN First !!!\n\n";
        return;
    }
    switch (currentUser->role) {
        case '1' : management(userHead,clinicHead,emDoctorHead); break;
        case '2' : Doctor(currentUser,clinicHead); break;
        case '3' : emDoctor(currentUser,emDoctorHead);break;
        case '4' : patient(currentUser,clinicHead,emDoctorHead,userHead); break;
        case '5' : pharmacy(userHead); break;
        case '6' : triage(currentUser,userHead,emDoctorHead); break;
        default: cout<<"\nINVALID !!!\n\n"; break;
    }

}


void editInformation(user* &currentUser, user* usedHead) {

    if (currentUser == nullptr) {
        cout<<"\nLOG IN First !!\n\n";
        return;
    }

    char choice = '\0';
    while (true){
        cout<<"\nSelect to Edit:\n"
            <<"[0]: Return To main Page\n"
            <<"[1]: First Name And Last Name\n"
            <<"[2]: Username\n"
            <<"[3]: Password\n"
            <<"[4]: Age\n"
            <<"[5]: ID\n"
            <<"--> ";
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        if (choice == '0')
            break;

        if (choice == '1') {
            string newFN, newLN;
            cout<<"New First Name:";
            getline(cin,newFN);

            cout<<"New Last Name:";
            getline(cin,newLN);

            cout<<"\nFirst Name Changed from "<<currentUser->firstName<<" To "<<newFN<<endl;
            cout<<"\nLast Name Changed from "<<currentUser->lastName<<" To "<<newLN<<endl;

            currentUser->firstName = newFN;
            currentUser->lastName = newLN;
        }


        else if (choice == '2') {

            string newUserName;

            cout<<"New Username:";
            getline(cin>>ws,newUserName);
            newUserName = toLowerCase(newUserName);

            if (newUserName == currentUser->userName){
                cout<<"\nThe new username is the same as the current one. No changes were made";
                return;
            }

            if (isUsernameTaken(usedHead, newUserName)){
                cout<<"\nThis Username is already taken !!\nReturning to the Menu...\n";
                return;
            }

            cout << "\nUsername changed from \"" << currentUser->userName << "\" to \"" << newUserName <<endl;
            currentUser->userName = newUserName;
        }

        else if (choice == '3'){

            string password;

            cout<<"\nEnter your current password to confirm the password change: ";
            getline(cin>>ws, password);

            if (password != currentUser->password) {
                cout << "\nthe Password does not match your current one";
                return;
            }

            string newPassword;
            cout<<"\nEnter new password: ";
            getline(cin>>ws, newPassword);

            if (newPassword == password){
                cout<<"\nThe new Password is the same as the current one. No changes were made";
                return;
            }
            cout<<"\nPassword Changed to "<< newPassword << endl;
            currentUser->password = newPassword;
        }


        else if (choice == '4') {

            string ageStr;
            cout<<"Age:";

            getline(cin,ageStr);

            try{
                currentUser->age = stoi(ageStr);
                cout<<"Age changed To "<<ageStr<<endl;
            }
            catch (invalid_argument& e) {
                cout << "Invalid Input for 'Age'. Please enter a valid integer: ";
            }
            catch (out_of_range& e) {
                cout << "Input is out of integer range (age). Try again: ";

            }

        }

        else if (choice == '5') {
            cout<<"ID:";
            getline(cin,currentUser->ID);
            cout<<"ID changed To "<< currentUser->ID <<endl;
        }

        else {
            cout<<"\nInvalid !\nTry Again..\n\n";
        }
    }
}



void mainPage(user* &userHead,clinic* &clinicHead,emergencyDoctor* &emDoctorHead) {
    char command = '\0';
    user* currentUser = userHead;
    while (true) {
        if (currentUser != nullptr)
            cout<<"\n\n< LOGGED in as "<<currentUser->userName<<" >\n";

        cout<<"\n[0]: Exit\n"
            <<"[1]: SIGN UP\n"
            <<"[2]: LOG IN\n"
            <<"[3]: LOG OUT\n"
            <<"[4]: Edit Information\n"
            <<"[5]: Actions\n"
            <<"--> ";

        cin>>command;

        if (command == '0')
            break;

        if (command == '1') {
            user* temp = newUser(userHead); // newUser() returns null if sign up failed
            currentUser = (temp != nullptr) ? temp : currentUser;
            // if newUser() returns null: the currentUser Value will not change
        }

        else if (command == '2') {
            user* temp = login(userHead); // login() returns null if sign up failed
            currentUser = (temp != nullptr) ? temp : currentUser;
            // if login() returns null: the currentUser Value will not change
        }

        else if (command == '3') {
            if (currentUser == nullptr)
                cout<<"\nNo User is logged in !!\n\n";
            else
                currentUser = nullptr;
        }


        else if (command == '4')
            editInformation(currentUser, userHead);


        else if(command == '5')
            userActions(currentUser,userHead,clinicHead,emDoctorHead);

        else
            cout<<"\n\nInvalid !! Please try again\n";
    }

}


void freeMemory(user* &usersHead, clinic* &clinicsHead, emergencyDoctor* &emDoctorsHead) {

    while (usersHead != nullptr) {
        user* temp = usersHead;
        usersHead = usersHead->next;
        delete temp;
    }

    while (clinicsHead != nullptr) {
        clinic* cTemp = clinicsHead;
        clinicsHead = clinicsHead->next;

        doctor* dTemp = cTemp->head;
        while (dTemp != nullptr) {
            doctor* toDelete = dTemp;
            dTemp = dTemp->next;
            delete toDelete;
        }

        delete cTemp;
    }

    while (emDoctorsHead != nullptr) {
        emergencyDoctor* temp = emDoctorsHead;
        emDoctorsHead = emDoctorsHead->next;
        delete temp;
    }
}


int main(){
    user* userHead = nullptr;
    clinic* clinicHead = nullptr;
    emergencyDoctor* emergencyDocHead = nullptr;

    mainPage(userHead, clinicHead, emergencyDocHead);

    freeMemory(userHead, clinicHead, emergencyDocHead);

    return 0;
}
