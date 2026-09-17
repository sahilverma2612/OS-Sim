#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>
#include "Process.h"

// One contiguous block of CPU execution, used to render the Gantt chart.
struct GanttEntry {
    int pid;
    int start;
    int end;
};

// Abstract base class for every CPU scheduling algorithm.
//
// Design note (interview talking point): this is an abstract class because
// every scheduling algorithm needs to answer the same question --
// "given these processes, produce an execution order" -- but each one
// answers it differently. Making schedule() pure virtual forces every
// derived class to provide its own algorithm while letting them all share
// the printing/metrics utility code below. This is runtime polymorphism:
// main.cpp can hold a Scheduler& and call schedule() without knowing which
// concrete algorithm it is at compile time.
class Scheduler {
public:
    virtual std::vector<GanttEntry> schedule(std::vector<Process>& processes) = 0;
    virtual std::string name() const = 0;
    virtual ~Scheduler() {}

    void printGanttChart(const std::vector<GanttEntry>& chart) const;
    void printMetricsTable(const std::vector<Process>& processes) const;

    double averageWaitingTime(const std::vector<Process>& processes) const;
    double averageTurnaroundTime(const std::vector<Process>& processes) const;
    double averageResponseTime(const std::vector<Process>& processes) const;
};

#endif
