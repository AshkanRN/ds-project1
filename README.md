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

### Roles
1. Management
2. Clinic Doctor
3. Emergency Doctor
4. Patient
5. Pharmacy
6. Triage

### Sign-Up Flow
1. User enters username, password, name, ID, age, and role.
2. Program checks username availability.
3. On success, account is created and stored in memory.

### Log-In Flow
1. User enters username and password.
2. If valid → redirected to role-specific menu.
3. If invalid → login rejected.

---

## Usage (Quick Walkthrough)
When you run the program, the main menu offers:

1. **Sign Up** — create an account
2. **Log In** — access role-based actions

### Role-specific actions:
- **Management (1)**: add clinics, add doctors (clinic/emergency), delete user, search users, list all users
- **Clinic Doctor (2)**: view patient queue, process visits, prescribe medicines
- **Patient (4)**: select clinic/doctor, join/cancel queue, go to triage
- **Triage (6) & Emergency Doctor (3)**: assign priority, serve patients by priority
- **Pharmacy (5)**: lookup patient by ID, dispense medicines (stack pop)

