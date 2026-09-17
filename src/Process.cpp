#include "../include/Process.h"

Process::Process(int pid, int arrivalTime, int burstTime, int priority)
    : pid(pid),
      arrivalTime(arrivalTime),
      burstTime(burstTime),
      priority(priority),
      completionTime(0),
      turnaroundTime(0),
      waitingTime(0),
      responseTime(-1),
      remainingTime(burstTime) {}
