# Hospital Management

**A Simple C++ hospital management system**  

+ [Project Assignment File](https://github.com/AshkanRN/ds-project1-gu/releases/download/dl/ds_project1-assignment.pdf)

---

## Overview


- Role-based accounts (management, clinic doctor, emergency doctor, patient, pharmacy, triage)
- Clinic registration and per-doctor patient queues (FIFO)
- Emergency triage with priority-based serving (priority queue)
- Pharmacy dispensing using per-patient medicine stacks (LIFO)
- All required data structures implemented manually (no STL containers used for the core structures)


---

## Features
- Sign-up / Log-in for different roles
- Management interface: add/delete users, add clinics, add doctors, search users
- Clinic doctors: view and serve patient queue, record prescribed medicines (pushed to patient stack)
- Emergency triage & doctors: triage assigns numeric priority; emergency doctors serve highest-priority patients first
- Pharmacy: lookup patient by ID and dispense medicines (pop from patient stack)
- Persistent in-memory structures for the program run (no file I/O / database)

---

## Data Structures
The following are built from scratch:
- **Singly linked list** — for lists of users, clinics, and doctors
- **Queue** — clinic patient queues (enqueue / dequeue / delete)
- **Priority queue (linked list based)** — emergency queue (smaller numeric value = higher urgency)
- **Stack** — each patient's medicine list (LIFO)


---

## Roles actions:
- **Management (1)**: add clinics, add doctors (clinic/emergency), delete user, search users, list all users
- **Clinic Doctor (2)**: view patient queue, process visits, prescribe medicines
- **Patient (4)**: select clinic/doctor, join/cancel queue, go to triage
- **Triage (6) & Emergency Doctor (3)**: assign priority, serve patients by priority
- **Pharmacy (5)**: lookup patient by ID, dispense medicines (stack pop)

---


## Requirements

- C++17 or later
- GCC / G++ compiler
- CMake 3.20+ *(only if using CMake method)*

---

## How to run

```bash
git clone https://github.com/AshkanRN/hospital-management-ds1.git
cd hospital-management-ds1
```

### Linux

#### Method 1: Using CMake (Recommended)

**Build:**
```bash
mkdir build && cd build

cmake ..

cmake --build .
```

**Run:**
```bash
./HospitalSystem
```

---

#### Method 2: Manual g++ (No CMake needed)

**Compile**
```bash
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o HospitalSystem
```

**Run**
```bash
./HospitalSystem
```

---

### Windows

**Using CMake:**
```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
HospitalSystem.exe
```

**Using manual g++:**
```bash
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o HospitalSystem.exe
HospitalSystem.exe
```

---