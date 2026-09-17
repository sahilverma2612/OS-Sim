#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "Scheduler.h"

// Non-preemptive Shortest Job First.
class SJFScheduler : public Scheduler {
public:
    std::vector<GanttEntry> schedule(std::vector<Process>& processes) override;
    std::string name() const override { return "Shortest Job First (Non-preemptive)"; }
};

#endif
