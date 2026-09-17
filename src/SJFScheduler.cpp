#include "../include/SJFScheduler.h"
#include <climits>
#include <algorithm>

// At every decision point, among the processes that have already arrived,
// pick the one with the smallest burst time. Once picked, it runs to
// completion (non-preemptive), which is why SJF can starve long jobs.
// Time complexity: O(n^2) with this simple linear scan per pick; could be
// improved to O(n log n) with a min-heap keyed by burst time.
std::vector<GanttEntry> SJFScheduler::schedule(std::vector<Process>& processes) {
    std::vector<GanttEntry> chart;
    int n = processes.size();
    std::vector<bool> done(n, false);
    int completed = 0;
    int currentTime = 0;

    while (completed < n) {
        int idx = -1;
        int minBurst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrivalTime <= currentTime &&
                processes[i].burstTime < minBurst) {
                minBurst = processes[i].burstTime;
                idx = i;
            }
        }

        if (idx == -1) {
            // No process has arrived yet -- fast-forward to the next arrival.
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
