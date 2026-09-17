#ifndef PROCESS_H
#define PROCESS_H

// Represents a single process with its scheduling attributes and
// the metrics computed once it has been scheduled.
class Process {
public:
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;       // lower number = higher priority

    // Computed after scheduling
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;   // -1 until the process gets its first CPU burst
    int remainingTime;  // used by preemptive algorithms (SRTF, Round Robin)

    Process(int pid, int arrivalTime, int burstTime, int priority = 0);
};

#endif
