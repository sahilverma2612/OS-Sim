#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "Scheduler.h"

class FCFSScheduler : public Scheduler {
public:
    std::vector<GanttEntry> schedule(std::vector<Process>& processes) override;
    std::string name() const override { return "First Come First Serve (FCFS)"; }
};

#endif
