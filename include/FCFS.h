#pragma once
#include "Scheduler.h"

class FCFSScheduler : public Scheduler {
public:
    std::string name() const override { return "FCFS"; }
    std::vector<Process> schedule(const std::vector<Process>& input,
                                  std::vector<GanttEntry>& gantt) override;
};
