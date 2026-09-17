#pragma once
#include "Scheduler.h"

class SJFScheduler : public Scheduler {
public:
    std::string name() const override { return "SJF (Non-Preemptive)"; }
    std::vector<Process> schedule(const std::vector<Process>& input,
                                  std::vector<GanttEntry>& gantt) override;
};
