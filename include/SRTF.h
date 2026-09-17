#pragma once
#include "Scheduler.h"

class SRTFScheduler : public Scheduler {
public:
    std::string name() const override { return "SRTF"; }
    std::vector<Process> schedule(const std::vector<Process>& input,
                                  std::vector<GanttEntry>& gantt) override;
};
