# OS-Sim — Operating System Simulator

> A C++ project I built to strengthen my understanding of Operating Systems and 
> implement the algorithms that I was studying practically instead of only 
> understanding them theoretically.

## About the Project

OS-Sim is a console-based Operating System Simulator developed using **C++17**.

While preparing Operating Systems for my placement interviews, I wanted to
implement concepts like CPU scheduling, page replacement and deadlock detection
myself. So I built this project as a small simulator where different OS
algorithms can be executed and their results can be compared.

## What I Implemented

### CPU Scheduling
- FCFS
- SJF (Non-Preemptive)
- SRTF
- Round Robin
- Priority Scheduling
- Gantt Chart
- Waiting Time, Turnaround Time, Response Time and Completion Time
- Comparison of scheduling algorithms

### Memory Management
- FIFO Page Replacement
- LRU Page Replacement
- Optimal Page Replacement
- Page Fault and Page Hit calculation

### Deadlock
- Banker's Algorithm
- Safe / Unsafe state detection
- Safe sequence generation

## OOP Used

The scheduling part of the project follows an object-oriented design.

I created a common abstract `Scheduler` class and implemented individual
scheduling algorithms as derived classes. This helped me use:

- Abstraction
- Inheritance
- Runtime Polymorphism
- Encapsulation
- STL containers

## Tech Stack

**C++17 | OOP | STL | Data Structures & Algorithms | Operating Systems**

## Project Structure

```text
OS-Sim/
├── include/
│   ├── Process.h
│   ├── Scheduler.h
│   ├── FCFS.h
│   ├── SJF.h
│   ├── SRTF.h
│   ├── RoundRobin.h
│   ├── Priority.h
│   ├── PageReplacement.h
│   └── Deadlock.h
│
├── src/
├── main.cpp
├── CMakeLists.txt
├── .gitignore
└── README.md
