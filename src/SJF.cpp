#include "SJF.h"
#include <algorithm>

std::vector<Process> SJFScheduler::schedule(
    const std::vector<Process>& input,
    std::vector<GanttEntry>& gantt) {

    std::vector<Process> p = input;
    std::vector<bool> done(p.size(), false);
    std::vector<Process> result;

    int completed = 0;
    int time = 0;
    const int n = static_cast<int>(p.size());

    while (completed < n) {
        int idx = -1;

        for (int i = 0; i < n; ++i) {
            if (done[i] || p[i].arrivalTime > time) continue;

            if (idx == -1 ||
                p[i].burstTime < p[idx].burstTime ||
                (p[i].burstTime == p[idx].burstTime &&
                 p[i].arrivalTime < p[idx].arrivalTime)) {
                idx = i;
            }
        }

        if (idx == -1) {
            int nextArrival = 1e9;
            for (int i = 0; i < n; ++i) {
                if (!done[i]) nextArrival = std::min(nextArrival, p[i].arrivalTime);
            }
            time = nextArrival;
            continue;
        }

        int start = time;
        p[idx].responseTime = start - p[idx].arrivalTime;
        time += p[idx].burstTime;
        p[idx].completionTime = time;

        gantt.push_back({p[idx].pid, start, time});
        done[idx] = true;
        result.push_back(p[idx]);
        ++completed;
    }

    calculateMetrics(result);
    return result;
}
