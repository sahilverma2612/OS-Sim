#include "SRTF.h"
#include <algorithm>
#include <climits>

std::vector<Process> SRTFScheduler::schedule(
    const std::vector<Process>& input,
    std::vector<GanttEntry>& gantt) {

    std::vector<Process> p = input;
    const int n = static_cast<int>(p.size());

    std::vector<int> remaining(n);
    std::vector<int> firstStart(n, -1);

    for (int i = 0; i < n; ++i)
        remaining[i] = p[i].burstTime;

    int completed = 0;
    int time = 0;

    while (completed < n) {
        int idx = -1;

        for (int i = 0; i < n; ++i) {
            if (p[i].arrivalTime <= time && remaining[i] > 0) {
                if (idx == -1 ||
                    remaining[i] < remaining[idx] ||
                    (remaining[i] == remaining[idx] &&
                     p[i].arrivalTime < p[idx].arrivalTime)) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; ++i) {
                if (remaining[i] > 0)
                    nextArrival = std::min(nextArrival, p[i].arrivalTime);
            }
            time = nextArrival;
            continue;
        }

        if (firstStart[idx] == -1) {
            firstStart[idx] = time;
            p[idx].responseTime = time - p[idx].arrivalTime;
        }

        // Execute for one time unit.
        std::string pid = p[idx].pid;

        if (!gantt.empty() && gantt.back().pid == pid && gantt.back().end == time) {
            gantt.back().end = time + 1;
        } else {
            gantt.push_back({pid, time, time + 1});
        }

        --remaining[idx];
        ++time;

        if (remaining[idx] == 0) {
            p[idx].completionTime = time;
            ++completed;
        }
    }

    calculateMetrics(p);
    return p;
}
