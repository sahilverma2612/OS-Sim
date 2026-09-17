#ifndef ROUND_ROBIN_SCHEDULER_H
#define ROUND_ROBIN_SCHEDULER_H

#include "Scheduler.h"

class RoundRobinScheduler : public Scheduler {
private:
    int quantum;

public:
    explicit RoundRobinScheduler(int q) : quantum(q) {}
    std::vector<GanttEntry> schedule(std::vector<Process>& processes) override;
    std::string name() const override {
        return "Round Robin (Quantum = " + std::to_string(quantum) + ")";
    }
};

#endif
