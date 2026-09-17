#pragma once
#include "Scheduler.h"

class RoundRobinScheduler : public Scheduler {
    int quantum;

public:
    explicit RoundRobinScheduler(int q) : quantum(q) {}

    std::string name() const override { return "Round Robin"; }
    std::vector<Process> schedule(const std::vector<Process>& input,
                                  std::vector<GanttEntry>& gantt) override;
};
