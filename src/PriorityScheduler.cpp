#include "../include/PriorityScheduler.h"
#include <climits>
#include <algorithm>

// Among arrived, not-yet-done processes, always pick the one with the
// smallest priority number. Non-preemptive: once picked, it runs to
// completion. This is why low-priority processes can starve -- a common
// interview follow-up, usually answered with "aging" (gradually boosting
// the effective priority of a waiting process).
std::vector<GanttEntry> PriorityScheduler::schedule(std::vector<Process>& processes) {
    std::vector<GanttEntry> chart;
    int n = processes.size();
    std::vector<bool> done(n, false);
    int completed = 0;
    int currentTime = 0;

    while (completed < n) {
        int idx = -1;
        int bestPriority = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrivalTime <= currentTime &&
                processes[i].priority < bestPriority) {
                bestPriority = processes[i].priority;
                idx = i;
            }
        }

        if (idx == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!done[i]) nextArrival = std::min(nextArrival, processes[i].arrivalTime);
            currentTime = nextArrival;
            continue;
        }

        Process& p = processes[idx];
        p.responseTime = currentTime - p.arrivalTime;

        int start = currentTime;
        currentTime += p.burstTime;

        p.completionTime = currentTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;

        chart.push_back({p.pid, start, currentTime});
        done[idx] = true;
        completed++;
    }
    return chart;
}
