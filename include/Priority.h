#pragma once
#include "Scheduler.h"

class PriorityScheduler : public Scheduler {
    bool preemptive;

public:
    explicit PriorityScheduler(bool isPreemptive)
        : preemptive(isPreemptive) {}

    std::string name() const override {
        return preemptive
            ? "Priority (Preemptive)"
            : "Priority (Non-Preemptive)";
    }

    std::vector<Process> schedule(const std::vector<Process>& input,
                                  std::vector<GanttEntry>& gantt) override;
};
