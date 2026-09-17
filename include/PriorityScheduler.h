#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include "Scheduler.h"

// Non-preemptive priority scheduling. Lower priority number = higher priority.
class PriorityScheduler : public Scheduler {
public:
    std::vector<GanttEntry> schedule(std::vector<Process>& processes) override;
    std::string name() const override { return "Priority Scheduling (Non-preemptive)"; }
};

#endif
