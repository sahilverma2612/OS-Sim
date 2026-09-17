#ifndef SRTF_SCHEDULER_H
#define SRTF_SCHEDULER_H

#include "Scheduler.h"

// Preemptive version of SJF: Shortest Remaining Time First.
class SRTFScheduler : public Scheduler {
public:
    std::vector<GanttEntry> schedule(std::vector<Process>& processes) override;
    std::string name() const override { return "Shortest Remaining Time First (Preemptive SJF)"; }
};

#endif
