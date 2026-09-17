#include "../include/SRTFScheduler.h"
#include <climits>

// Simulated one time unit at a time. At every tick, the process with the
// smallest remaining burst time (among those that have arrived) runs for
// one unit. If a shorter job arrives mid-execution, it preempts the
// current one -- that's the key difference from SJF.
// Time complexity: O(n * totalBurstTime) with this tick-by-tick simulation.
std::vector<GanttEntry> SRTFScheduler::schedule(std::vector<Process>& processes) {
    std::vector<GanttEntry> chart;
    int n = processes.size();
    for (auto& p : processes) p.remainingTime = p.burstTime;

    int completed = 0;
    int currentTime = 0;
    int lastPid = -1;
    int segmentStart = 0;

    while (completed < n) {
        int idx = -1;
        int minRemaining = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 &&
                processes[i].remainingTime < minRemaining) {
                minRemaining = processes[i].remainingTime;
                idx = i;
            }
        }

        if (idx == -1) {
            currentTime++;  // CPU idle, no process has arrived yet
            continue;
        }

        Process& p = processes[idx];
        if (p.responseTime == -1) p.responseTime = currentTime - p.arrivalTime;

        if (lastPid != p.pid) {
            if (lastPid != -1) chart.push_back({lastPid, segmentStart, currentTime});
            segmentStart = currentTime;
            lastPid = p.pid;
        }

        p.remainingTime--;
        currentTime++;

        if (p.remainingTime == 0) {
            p.completionTime = currentTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            completed++;
            chart.push_back({lastPid, segmentStart, currentTime});
            lastPid = -1;
        }
    }
    return chart;
}
