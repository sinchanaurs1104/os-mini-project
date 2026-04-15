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

### Build
make

### Load Module
sudo insmod monitor.ko

### Verify Device
ls -l /dev/container_monitor

### Start Supervisor
sudo ./engine supervisor ./rootfs-base

### Start Containers
sudo ./engine start alpha ./rootfs-alpha "echo HELLO"
sudo ./engine start beta ./rootfs-beta "echo WORLD"

### View Logs
cat logs/alpha.log
cat logs/beta.log

### Stop Containers
sudo ./engine stop alpha
sudo ./engine stop beta

---

## 3. Demo

- Multi-container supervision  
- Metadata tracking  
- Logging system  
- CLI and IPC  
- Soft-limit warning  
- Hard-limit enforcement  
- Scheduling experiment  
- Clean teardown  

---

## 4. Summary

This project implements a lightweight container runtime in C with supervisor architecture, logging pipeline, and kernel memory monitoring.
