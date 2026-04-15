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

```bash
make
```

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

## 4. Engineering Analysis

### 1. Isolation Mechanisms
Modern operating systems provide isolation to ensure that processes do not interfere with each other. In this project, isolation is achieved using chroot, which restricts a process to a specific directory as its root filesystem.

This simulates container-like behavior by ensuring that each container has its own independent filesystem view. Although all containers share the same underlying kernel, filesystem isolation prevents processes from accessing files outside their designated environment.

---

### 2. Supervisor and Process Lifecycle
A supervisor process manages the lifecycle of all containers, including creation, execution, and termination.

It uses system calls like fork() and exec(), tracks execution, and reaps child processes to prevent zombies.

---

### 3. IPC and Synchronization
UNIX domain sockets are used for communication between the CLI and the supervisor.

The logging system follows a producer-consumer model where container output is captured and written to log files safely.

---

### 4. Memory Management
Memory is monitored using a kernel module with soft and hard limits.

Soft limit generates warnings, while hard limit terminates the process when exceeded.

---

### 5. Scheduling Behavior
CPU-bound workloads demonstrate how the Linux scheduler distributes CPU time among processes, ensuring fairness.

---

## 5. Design Decisions and Tradeoffs

### Namespace Isolation
- Choice: chroot  
- Tradeoff: limited isolation  
- Reason: simple implementation  

### Supervisor Architecture
- Choice: single supervisor  
- Tradeoff: less scalable  
- Reason: easier control  

### IPC and Logging
- Choice: UNIX sockets + file logging  
- Tradeoff: no real-time streaming  
- Reason: simple and reliable  

### Kernel Monitor
- Choice: ioctl-based kernel module  
- Tradeoff: complex implementation  
- Reason: direct kernel interaction  

### Scheduling Experiments
- Choice: CPU-bound workloads  
- Tradeoff: limited scenarios  
- Reason: clear demonstration  

---

## 6. Scheduler Experiment Results

| Container | Process  | CPU Usage |
|----------|---------|----------|
| c1       | cpu_hog | ~50%     |
| c2       | cpu_hog | ~50%     |

Both processes received approximately equal CPU time.

This demonstrates that the Linux scheduler ensures fair CPU distribution among processes.
