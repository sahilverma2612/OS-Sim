#include "RoundRobin.h"
#include <algorithm>
#include <queue>

std::vector<Process> RoundRobinScheduler::schedule(
    const std::vector<Process>& input,
    std::vector<GanttEntry>& gantt) {

    std::vector<Process> p = input;
    const int n = static_cast<int>(p.size());

    std::vector<int> remaining(n);
    for (int i = 0; i < n; ++i)
        remaining[i] = p[i].burstTime;

    std::vector<bool> added(n, false);
    std::queue<int> readyQueue;

    int time = 0;
    int completed = 0;

    while (completed < n) {
        // Add all processes that have arrived.
        for (int i = 0; i < n; ++i) {
            if (!added[i] && p[i].arrivalTime <= time) {
                readyQueue.push(i);
                added[i] = true;
            }
        }

        if (readyQueue.empty()) {
            int nextArrival = 1e9;
            for (int i = 0; i < n; ++i) {
                if (!added[i])
                    nextArrival = std::min(nextArrival, p[i].arrivalTime);
            }
            time = nextArrival;
            continue;
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        if (p[idx].responseTime == -1) {
            p[idx].responseTime = time - p[idx].arrivalTime;
        }

        int runTime = std::min(quantum, remaining[idx]);
        int start = time;
        time += runTime;
        remaining[idx] -= runTime;

        if (!gantt.empty() && gantt.back().pid == p[idx].pid &&
            gantt.back().end == start) {
            gantt.back().end = time;
        } else {
            gantt.push_back({p[idx].pid, start, time});
        }

        // Add newly arrived processes before re-queuing current process.
        for (int i = 0; i < n; ++i) {
            if (!added[i] && p[i].arrivalTime <= time) {
                readyQueue.push(i);
                added[i] = true;
            }
        }

        if (remaining[idx] > 0) {
            readyQueue.push(idx);
        } else {
            p[idx].completionTime = time;
            ++completed;
        }
    }

    calculateMetrics(p);
    return p;
}
