#include "Priority.h"
#include <algorithm>
#include <climits>

std::vector<Process> PriorityScheduler::schedule(
    const std::vector<Process>& input,
    std::vector<GanttEntry>& gantt) {

    std::vector<Process> p = input;
    const int n = static_cast<int>(p.size());

    if (!preemptive) {
        std::vector<bool> done(n, false);
        std::vector<Process> result;
        int completed = 0;
        int time = 0;

        while (completed < n) {
            int idx = -1;

            for (int i = 0; i < n; ++i) {
                if (done[i] || p[i].arrivalTime > time) continue;

                // Smaller number = higher priority.
                if (idx == -1 ||
                    p[i].priority < p[idx].priority ||
                    (p[i].priority == p[idx].priority &&
                     p[i].arrivalTime < p[idx].arrivalTime)) {
                    idx = i;
                }
            }

            if (idx == -1) {
                int nextArrival = INT_MAX;
                for (int i = 0; i < n; ++i)
                    if (!done[i]) nextArrival = std::min(nextArrival, p[i].arrivalTime);
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

    // Preemptive priority scheduling.
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
                    p[i].priority < p[idx].priority ||
                    (p[i].priority == p[idx].priority &&
                     p[i].arrivalTime < p[idx].arrivalTime)) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; ++i)
                if (remaining[i] > 0) nextArrival = std::min(nextArrival, p[i].arrivalTime);
            time = nextArrival;
            continue;
        }

        if (firstStart[idx] == -1) {
            firstStart[idx] = time;
            p[idx].responseTime = time - p[idx].arrivalTime;
        }

        if (!gantt.empty() && gantt.back().pid == p[idx].pid &&
            gantt.back().end == time) {
            gantt.back().end = time + 1;
        } else {
            gantt.push_back({p[idx].pid, time, time + 1});
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
