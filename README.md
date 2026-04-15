# Multi-Container Runtime and Kernel Monitor

## 1. Team Information

Member 1:  
Name – Bindu I  
SRN – PES1UG24CS659  

Member 2:  
Name – Sinchana Urs  
SRN – PES1UG24CS626  

---

## 2. Build, Load, and Run Instructions

Step-by-step commands to build, load, and run the project on Ubuntu 22.04/24.04.

---

### Build
---

### Load kernel module

```bash
sudo insmod monitor.ko
```bash
make

---

## 3. Demo with Screenshots

### 1. Multi-container supervision
<img width="940" height="74" alt="image" src="https://github.com/user-attachments/assets/0a5eb77e-da61-463e-a830-a3b1b3474a1e" />

<img width="940" height="153" alt="image" src="https://github.com/user-attachments/assets/0ff7a9fd-efd3-4958-ba59-42acc0b07923" />

<img width="940" height="885" alt="image" src="https://github.com/user-attachments/assets/fce32ba7-d1bc-4f72-8327-e0014cce6413" />

Two containers running under one supervisor with different PIDs.

---

### 2. Metadata tracking
<img width="940" height="128" alt="image" src="https://github.com/user-attachments/assets/a6fbd0c2-5f6a-4b8b-95e9-84af6ef82f2c" />



Shows container ID, PID, and state.

---

### 3. Bounded-buffer logging

<img width="940" height="139" alt="image" src="https://github.com/user-attachments/assets/8e19003b-f54e-4d15-a600-938bc36b833c" />


Container output stored in log files.

---

### 4. CLI and IPC

<img width="940" height="128" alt="image" src="https://github.com/user-attachments/assets/b161b781-ea53-4a42-a26a-b5b651c9bd46" />


CLI command sent to supervisor and response received.

---

### 5. Soft-limit warning

<img width="940" height="280" alt="image" src="https://github.com/user-attachments/assets/2586aeff-c1ee-453c-aea1-de56f78789a1" />


Kernel logs showing soft limit warning.

---

### 6. Hard-limit enforcement

<img width="940" height="280" alt="image" src="https://github.com/user-attachments/assets/74ddba82-9700-40ef-a2b1-7d0da19ed7cc" />


Kernel logs showing hard limit enforcement.

---

### 7. Scheduling experiment
<img width="940" height="826" alt="image" src="https://github.com/user-attachments/assets/38a14b0e-7a67-48f1-a335-50ff62d80360" />



CPU usage visible in top command.

---

### 8. Clean teardown

<img width="940" height="81" alt="image" src="https://github.com/user-attachments/assets/47578ab0-e5b5-4668-923c-db11ea3ab199" />


No zombie processes after execution.

## 4. Summary

This project implements a lightweight container runtime in C with supervisor architecture, logging pipeline, and kernel memory monitoring.
