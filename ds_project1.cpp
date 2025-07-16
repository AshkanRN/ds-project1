#include <iostream>
#include <limits>
#include <string>
using namespace std;



string toLowerCase(string &str) {
    for (int i = 0 ; i < str.length() ; i++)
        str[i] = (str[i] >= static_cast<int>('A') && str[i] <= 'Z') ? (str[i] + 32) : str[i];
    return str;
}


class visitQueue;
class medicine;
class emergencyQueue;

class user {
public:
    string firstName , lastName , ID  , userName , password,age;
    char role; // '1': management / '2': clinic doctor / '3' : emergency doctor / '4': patient / '5': pharmacy / '6': triage
    user* next;
    medicine* med;

    user() {
        next = nullptr;
        med = nullptr;
    }

};



class doctor {
public:
    string docName;
    visitQueue* queue;

    doctor* next;
    doctor() {
        next = nullptr;
        queue = nullptr;
    }
};


int clinicCount = 0;
class clinic {
public:
    string clinicName;
    doctor* head = nullptr;
    int doctorsCount = 0;

    clinic* next;
    clinic() {
        next = nullptr;
    }
};

class visitQueue {
public:
    struct node {
        user* patient;

        node* next;
        node() {
            next = nullptr;
            patient = nullptr;
        }
    };

    node* front , *rear;

    visitQueue() {
        front = rear = nullptr;
    }
    bool isEmpty() const {
        return front == nullptr;
    }
    void enqueue(user* newPatient) {
        node* newNode = new node;
        newNode->patient = newPatient;

        if (isEmpty())
            rear = front = newNode;

        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            cout<<"\nThe Queue Is Empty\n"<<endl;
            return;
        }
        node* temp = front;
        front = front->next;
        delete temp;

        if (front == nullptr)
            rear = nullptr;
    }
    void printQueue() const {
        if (isEmpty()) {
            cout<<"\nThere is NO Patient in The Queue !!\n\n";
            return;
        }

        node* ptr = front;
        int postion = 1;
        cout<<endl;
        while (ptr != nullptr) {
            cout<<postion++<<".  "<<ptr->patient->firstName<<"  "<<ptr->patient->lastName<<" -- ID:"<<ptr->patient->ID<<" -- Age:"<<ptr->patient->age<<endl;
            ptr = ptr->next;
        }
        cout<<endl;
    }

    void deleteFromQueue(user* &target) {

        if (front == nullptr) {
            cout<<"\nThe Queue Is EMPTY !!\n\n";
            return;
        }

        node* ptr = front;

        if (front->patient == target) {
            dequeue();
            return;
        }

        while (ptr != nullptr) {
            if (ptr->next->patient == target)
                break;
            ptr = ptr->next;
        }

        if (ptr->next == nullptr) {
            cout << "Patient not found in the queue.\n";
            return;

        }

        node* temp = ptr->next;
        ptr->next = temp->next;

        if (temp == rear)
            rear = ptr;

        delete temp;

    }
};


int emDoctorCount = 0;
class emergencyDoctor {
public:
    string docName;
    emergencyQueue* queue;

    emergencyDoctor* next;
    emergencyDoctor() {
        next = nullptr;
        queue = nullptr;
    }
};


class emergencyQueue {
public:
    struct node {
        user* patient;
        int priority;

        node* next;

        node() {
            next = nullptr;
            priority = NULL;
            patient = nullptr;

        }
    };

    node* head;
    emergencyQueue() {
        head = nullptr;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void enqueue(user* patient,int priority) {
        node* newNode = new node;
        newNode->patient = patient;
        newNode->priority = priority;


        if ( isEmpty() || priority < head->priority) {
            newNode->next = head;
            head = newNode;
        } else {

            node* current = head;
            while (current->next != nullptr && current->next->priority <= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            cout<<"\nThe Queue Is Empty\n\n";
            return;
        }
        node* temp = head;
        head = head->next;
        delete temp;
    }

    void printQueue() const {
        if (isEmpty()) {
            cout<<"\nThere is NO Patient in The Queue !!\n\n";
            return;
        }

        node* current = head;
        int postion = 1;

        cout<<endl;
        while (current != nullptr) {
            cout<<postion++<<".  "<<current->patient->firstName<<"  "<<current->patient->lastName
                <<" -- ID:"<<current->patient->ID<<" -- Age:"<<current->patient->age<<endl;
            current = current->next;
        }
        cout<<endl;
    }
};


// Stack for Medicine
class medicine {
public:
    struct node {
        string medicineName;
        node* next;
        node() {
            next = nullptr;
        }
    };

    node* top;

    medicine() {
        top = nullptr;
    }

    bool isEmpty() const {
        return (top == nullptr);
    }
    void push(const string &medName) {
        node* newNode = new node;
        newNode->medicineName = medName;

        newNode->next = top;
        top = newNode;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    string pop() {
        if (isEmpty()) {
            cout<<"Stack is Empty !!"<<endl;
            return "";
        }
        node* temp = top;
        string medName = top->medicineName;
        delete temp;
        top = top->next;

        return medName;
    }
    void printMedicine() const {

        // isEmpty Condition considered in pharmacy

        node* temp = top;
        while (temp != nullptr) {
            cout<<temp->medicineName<<endl;
            temp = temp->next;
        }
    }
};



user* newUser(user* &first) {

    user* newNode = new user;

    cout<<" <  Sign-Up  > "<<endl;

    cout<<"Username:";      getline(cin>>ws,newNode->userName);
    newNode->userName = toLowerCase(newNode->userName);

    user* ptr = first;
    while (ptr != nullptr) {
        if (ptr->userName == newNode->userName) {
            cout<<"\nThis Username is already taken !!\nReturning to the Menu...\n\n";
            delete newNode;
            return nullptr;
        }
        ptr = ptr->next;
    }
    delete ptr;

    cout<<"Password:";      getline(cin,newNode->password);

    cout<<"First Name:";    getline(cin,newNode->firstName);
    newNode->firstName = toLowerCase(newNode->firstName);

    cout<<"Last Name:";     getline(cin,newNode->lastName);
    newNode->lastName = toLowerCase(newNode->lastName);

    cout<<"ID:";            getline(cin,newNode->ID);

    cout<<"Age:";           getline(cin,newNode->age);

    cout<<"Select Role:"
          "\n[1]management"
          "\n[2]clinic doctor"
          "\n[3]emergency doctor"
          "\n[4]patient"
          "\n[5]pharmacy"
          "\n[6]triage:";

    cin>>newNode->role;

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
        cout<<"\nThere is No User Yet !!\n"<<endl;
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
        default: cout<<"????\n"; break;
    }

}

void printAllUsers(user* first){ // print content of All nodes (in user Linked list)
    if (first == nullptr) {
        cout<<"There is No User Yet !!"<<endl;
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

void addClinic(clinic* &first) {

    clinic* newClinic = new clinic;

    cout<<"Clinic Name:";
    getline(cin>>ws,newClinic->clinicName);

    if (first == nullptr)
        first = newClinic;

    else {
        newClinic->next = first;
        first = newClinic;
    }
    clinicCount++;
}

void printClinics(clinic * first); // printClinics() Prototype

void addDrToClinic(clinic* &first1,user* &first2) {

    if (first1 == nullptr) {
        cout<<"\nNo Clinic Added yet !\n\n";
        return;
    }

    user* temp = newUser(first2);

    if (temp == nullptr)
        return;

    doctor* newDoctor = new doctor;
    newDoctor->queue = new visitQueue;

    newDoctor->docName = temp->firstName+" "+temp->lastName;

    cout<<"Add to which Clinic?"<<endl;
    printClinics(first1);

    clinic * ptr = first1;

    int command = NULL;
    cin>>command;

    if (command < 1 || command > clinicCount) {
        cout << "Invalid clinic choice. Please try again.\n";
        delete newDoctor;
        return;
    }

    for (int i = 0; i < command-1 ; i++)
        ptr = ptr->next;

    // for buffer problem
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    if (ptr->head == nullptr)
        ptr->head = newDoctor;
    else {
        newDoctor->next = ptr->head;
        ptr->head = newDoctor;
    }
    ptr->doctorsCount++;

}

void printClinics(clinic *first) {
    if (first == nullptr) {
        cout<<"no Clinic added yet"<<endl;
        return;
    }

    clinic* ptr = first;

    int i = 1;
    while (ptr != nullptr) {
        cout<<i++<<"."<<ptr->clinicName<<endl;
        ptr = ptr->next;
    }
}

void printDoctors(const clinic* clinicPtr) {
    if (clinicPtr == nullptr) {
        cout<<"\nThere is No clinic\n\n";
        return;
    }
    doctor* temp = clinicPtr->head; // head is head of The doctors list in the The clinic
    if (temp == nullptr) {
        cout<<"\nThere is No Doctor\n\n";
        return;
    }
    int i = 1;
    while (temp != nullptr) {
        cout<<i++<<"."<<temp->docName<<endl;
        temp = temp->next;
    }
}

void printEmDoctor(emergencyDoctor* emDoctorHead) {
    if (emDoctorHead == nullptr) {
        cout<<"\nNo Emergency Doctor Available\n\n";
        return;
    }
    emergencyDoctor* ptr = emDoctorHead;

    int i = 1;
    while (ptr != nullptr) {
        cout<<i++<<"."<<ptr->docName<<endl;
        ptr = ptr->next;
    }
}


void printClinicDoctors(clinic *first) {

    if (first == nullptr) {
        cout<<"no Clinic added yet"<<endl;
        return;
    }

    cout<<"Select Clinic (1 to "<<clinicCount<<")"<<endl;
    printClinics(first);

    clinic * ptr = first;

    int command = NULL;
    cin>>command;
    for (int i = 0; i < command-1; i++) {
        ptr = ptr->next;
    }

    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    doctor* ptr2 = ptr->head;

    int i = 1;
    while (ptr2 != nullptr) {
        cout<<"["<<i++<<"] (Clinic: "<<ptr->clinicName<<"): "<<ptr2->docName<<endl;
        ptr2 = ptr2->next;

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

// عملیات های متصدی داروخانه
void pharmacy(user* usersHead) {
    if (usersHead == nullptr) {
        cout<<"\nNo Patient Available\n\n";
        return;
    }
    user* currentPatient = nullptr;

    char choice = '\0';

    while (true) {
        if (currentPatient != nullptr)
            cout<<"Patient: "<<currentPatient->firstName<<" "<<currentPatient->lastName<<endl;;
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
                cout<<"medicines has not been registered yet !! \n\n";
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
        cout<<"\nThere is NO USER Yet !! please SIGN UP\n\n";
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



doctor* findDoctorInUsers(const user* currentUser, clinic* clinicHead) {
    if (clinicHead == nullptr) {
        cout << "\nNo Clinics Available\n\n";
        return nullptr;
    }

    clinic* clinicTemp = clinicHead;
    string name = currentUser->firstName + " " + currentUser->lastName;
    while (clinicTemp != nullptr) {
        doctor* doctorTemp = clinicTemp->head;

        while (doctorTemp != nullptr) {
            if (name == doctorTemp->docName) {
                return doctorTemp;
            }
            doctorTemp = doctorTemp->next;
        }
        clinicTemp = clinicTemp->next;
    }

    cout << "\nDoctor Not Found\n\n";
    return nullptr;
}

emergencyDoctor* findEmDoctorInUsers(const user* currentUser, emergencyDoctor* &emergencyDoctorsHead) {
    if (emergencyDoctorsHead == nullptr) {
        cout << "\nNo Emergency Doctor Available\n\n";
        return nullptr;
    }

    emergencyDoctor* docTemp = emergencyDoctorsHead;
    string name = currentUser->firstName + " " + currentUser->lastName;

    while (docTemp != nullptr) {
        if (name == docTemp->docName) {
            return docTemp;
        }
        docTemp = docTemp->next;
    }

    cout << "\nEmergency Doctor Not Found\n\n";
    return nullptr;
}


// Clinic Doctor
void Doctor(user* &currentUser,clinic* &clinicHead) {
    if (clinicHead == nullptr) {
        cout << "\nNo Clinics Available\n\n";
        return;
    }
    char command = '\0';
    doctor* currentDoc = findDoctorInUsers(currentUser,clinicHead);
    if (currentDoc == nullptr) {
        cout<<"\nSomething Went Wrong\n\n";
        return;
    }
    while (true) {
        cout<<"\n[0]: Return To The Main Page\n"
            <<"[1]: Patients Lsit\n"
            <<"[2]: Visit\n";
        cin>>command;
        if (command == '0')
            break;
        if (command == '1') {
            currentDoc->queue->printQueue();
        }
        else if (command == '2') {
            if (currentDoc->queue->isEmpty()) {
                cout<<"\nNo Patient To Visit\n\n";
                continue;
            }
            user* patient = currentDoc->queue->front->patient;
            char need = '\0';
            cout<<"Patient's name: "<<patient->firstName<<" "<<patient->lastName<<" -- age: "<<patient->age;
            cout<<"\nNeeds Medicine? [y/n]:\n";
            cin>>need;

            // cin.ignore(numeric_limits<streamsize>::max(),'\n');

            if (need == 'y' || need == 'Y' ) {
                int medCount = NULL;
                cout<<"\nHow many medicines does The Patient needs?";
                cin>>medCount;

                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                string temp;
                for (int i = 0; i < medCount; i++) {
                    cout<<"Medicine "<<i+1<<":";
                    // getline(cin,temp);
                    cin>>temp;
                    patient->med->push(temp);
                }
                cout<<"DONE !\n";
                currentDoc->queue->dequeue();
            }
            else if (need == 'n' || need == 'N') {
                cout<<"DONE !"<<endl;
                currentDoc->queue->dequeue();
            }
            else
                cout<<"\nInvalid !!\n";

        }
    }
}

// EmergencyDoctor
void emDoctor(user* &currentUser, emergencyDoctor* &emergencyDoctorsHead) {
    char command = '\0';

    // Fine Emergency Doctor In Users List
    emergencyDoctor* currentDoc = findEmDoctorInUsers(currentUser, emergencyDoctorsHead);
    if (currentDoc == nullptr) {
        cout << "\nSomething Went Wrong\n\n";
        return;
    }

    while (true) {
        cout << "\n[0]: Return To The Main Page\n"
             << "[1]: Emergency Patients List\n"
             << "[2]: Start Emergency Visit\n";
        cin >> command;

        if (command == '0')
            break;

        if (command == '1') {
            currentDoc->queue->printQueue();
        }
        else if (command == '2') {
            if (currentDoc->queue->isEmpty()) {
                cout << "\nNo Patient To Visit\n\n";
                continue;
            }

            user* patient = currentDoc->queue->head->patient;
            cout << "Patient's name: " << patient->firstName << " " << patient->lastName << " -- Age: " << patient->age << endl;

            char need = '\0';
            cout << "\nDoes the patient need medicine? [y/n]:\n";
            cin >> need;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (need == 'y' || need == 'Y') {
                int medCount = NULL;
                cout << "\nHow many medicines does the patient need?";
                cin >> medCount;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string temp;
                for (int i = 0; i < medCount; i++) {
                    cout << "Medicine " << i + 1 << ":";
                    cin >> temp;
                    patient->med->push(temp);
                }
                cout << "DONE!\n";
                currentDoc->queue->dequeue();
            }
            else if (need == 'n' || need == 'N') {
                cout << "DONE!" << endl;
                currentDoc->queue->dequeue();
            }
            else {
                cout << "\nInvalid input!!\n";
            }
        }
    }
}



void triage(user* currentPatient,user* &userHead,emergencyDoctor* &emDoctorHead);

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
            <<"[1]: Make an Appointment (Nobat)\n"
            <<"[2]: Cancel The Appointment\n"
            <<"[3]: Emergency\n";
        cin >> command;


        if (command == '0')
            return;

        if (command == '1') {
            if (clinicHead == nullptr) {
                cout<<"\nNo Clinic Added Yet \n\n";
                continue;
            }
            int clinicChoice = NULL;

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

            int doctorChoice = NULL;
            if (selectedClinic->head == nullptr) {
                cout<<"\nThere Is no Doctor in "<<selectedClinic->clinicName<<"\n\n";
                continue;
            }
            cout<<"Select a Doctor in "<<selectedClinic->clinicName<<endl;
            printDoctors(selectedClinic);
            cin>>doctorChoice;

            if (doctorChoice < 1 || doctorChoice > selectedClinic->doctorsCount) {
                cout << "Invalid doctor choice. Please try again.\n";
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
            cout<<"\n  <   Trige  >  \n";
            triage(currentUser,userHead,emDoctorHead);
        }
    }

}


void addEmergencyDoctor(user* &usersHead, emergencyDoctor* &emDoctorsHead) {

    user* temp = newUser(usersHead);
    if (temp == nullptr) {
        cout << "Error in user creation.\n Returning to management Menu...\n";
        return;
    }


    emergencyDoctor* newDoctor = new emergencyDoctor;
    newDoctor->queue = new emergencyQueue;

    newDoctor->docName = temp->firstName + " " + temp->lastName;


    newDoctor->next = emDoctorsHead;
    emDoctorsHead = newDoctor;

    cout << "\nEmergency Doctor " << newDoctor->docName << " added successfully.\n";
    emDoctorCount++;
}


void assignPatientToEmergency(user* &patient, int priority, emergencyDoctor* &currentDoctor) {
    if (patient == nullptr || currentDoctor == nullptr) {
        cout << "\nInvalid patient or doctor information.\n" << endl;
        return;
    }
    currentDoctor->queue->enqueue(patient, priority);
    cout << "\nPatient " << patient->firstName << " " << patient->lastName << " added to emergency queue\n\n";
}

void triage(user* currentPatient,user* &userHead,emergencyDoctor* &emDoctorHead) {
    if (userHead == nullptr) {
        cout<<"\nThere Is no User\n\n";
        return;
    }
    if (emDoctorCount == 0) {
        cout<<"\nNo Emergency Doctor Available\n\n";
        return;
    }

    int choice = NULL;

    cout<<"Select The Doctor:\n";
    printEmDoctor(emDoctorHead);

    cin>>choice;

    if (choice < 1 || choice > emDoctorCount) {
        cout << "Invalid choice. Please try again.\n";
        return;
    }

    emergencyDoctor* currentDoctor = emDoctorHead;

    for (int i = 0; i < choice-1; i++)
        currentDoctor = currentDoctor->next;

    string ID;
    cout<<"Enter Patient's ID:";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,ID);

    user* check = searchPatientID(userHead,ID);

    if (check == nullptr)
        currentPatient = newUser(userHead);

    int prio;
    cout<<"Enter Priority Code:";
    cin>>prio;

    assignPatientToEmergency(currentPatient,prio,currentDoctor);
}

void deleteUser(user* &usersHead) {
    if (usersHead == nullptr) {
        cout<<"\nThere is No User to Delete\n\n";
        return;
    }
    string username,password;

    cout<<"Username:";  getline(cin>>ws,username);
    cout<<"Password:";  getline(cin>>ws,password);

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
    }
    else {
        prev->next = ptr->next;
        ptr->next = nullptr;
        delete ptr;
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
        cout<<"\nLOG-IN First !!!\n\n";
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

void editInformation(user* &currentUser) {

    if (currentUser == nullptr) {
        cout<<"\nLOG IN First !!\n\n";
        return;
    }
    char choice = '\0';
    while (true){
        cout<<"Edit ...?\n"
            <<"[0]: Return To main Page\n"
            <<"[1]: First Name And Last Name\n"
            <<"[2]: Username And Password\n"
            <<"[3]: Age\n"
            <<"[4]: ID\n";
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        if (choice == '0')
            break;

        if (choice == '1') {
            cout<<"First Name:";
            getline(cin,currentUser->firstName);
            cout<<"Last Name:";
            getline(cin,currentUser->lastName);
        }
        else if (choice == '2') {
            cout<<"Username:";
            getline(cin,currentUser->userName);
            cout<<"Password:";
            getline(cin,currentUser->password);
        }
        else if (choice == '3') {
            cout<<"Age:";
            getline(cin,currentUser->age);
        }
        else if (choice == '4') {
            cout<<"ID:";
            getline(cin,currentUser->ID);
        }
        else {
            cout<<"\nInvalid !\nTry Agagin..\n\n";
        }
    }
}

void mainPage(user* &userHead,clinic* &clinicHead,emergencyDoctor* &emDoctorHead) {
    char command = '\0';
    user* currentUser = userHead;
    while (true) {
        if (currentUser != nullptr)
            cout<<"\n\nLOGGED in as "<<currentUser->userName<<"\n";
        cout<<"[0]: Exit\n"
            <<"[1]: SIGN UP\n"
            <<"[2]: LOG IN\n"
            <<"[3]: LOG OUT\n"
            <<"[4]: Edit Information\n"
            <<"[5]: Actions\n"
            <<":";

        cin>>command;

        if (command == '0')
            break;

        if (command == '1') {
            user* temp = newUser(userHead); // newUser() returns null if sign up failed
            currentUser = (temp != nullptr) ? temp : currentUser; // if newUser() returns null: the currentUser Value will not change
        }
        else if (command == '2') {
            user* temp = login(userHead); // // login() returns null if sign up failed
            currentUser = (temp != nullptr) ? temp : currentUser; // if login() returns null: the currentUser Value will not change
        }

        else if (command == '3') {
            if (currentUser == nullptr)
                cout<<"\nNo User is logged in !!\n\n";
            else
                currentUser = nullptr;
        }


        else if (command == '4')
            editInformation(currentUser);


        else if(command == '5')
            userActions(currentUser,userHead,clinicHead,emDoctorHead);

        else
            cout<<"\nInvalid !! Please try again\n\n";
    }

}

int main(){

    user* first1=nullptr;
    clinic* first2=nullptr;
    emergencyDoctor* first3=nullptr;
    mainPage(first1,first2,first3);


    return 0;
}


