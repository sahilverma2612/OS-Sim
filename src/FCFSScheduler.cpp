#include "../include/FCFSScheduler.h"
#include <algorithm>

// FCFS: run processes strictly in arrival order, one at a time.
// Time complexity: O(n log n) for the sort, O(n) for the simulation -> O(n log n) overall.
std::vector<GanttEntry> FCFSScheduler::schedule(std::vector<Process>& processes) {
    std::vector<GanttEntry> chart;

    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) { return a.arrivalTime < b.arrivalTime; });

    int currentTime = 0;
    for (auto& p : processes) {
        if (currentTime < p.arrivalTime) currentTime = p.arrivalTime; // CPU idles until arrival
        p.responseTime = currentTime - p.arrivalTime;

        int start = currentTime;
        currentTime += p.burstTime;

        p.completionTime = currentTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;

        chart.push_back({p.pid, start, currentTime});
    }
    return chart;
}
