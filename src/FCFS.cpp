#include "FCFS.h"
#include <algorithm>

std::vector<Process> FCFSScheduler::schedule(
    const std::vector<Process>& input,
    std::vector<GanttEntry>& gantt) {

    std::vector<Process> p = input;

    std::stable_sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int time = 0;

    for (auto& current : p) {
        if (time < current.arrivalTime) {
            time = current.arrivalTime;
        }

        int start = time;

        if (current.responseTime == -1) {
            current.responseTime = start - current.arrivalTime;
        }

        time += current.burstTime;
        current.completionTime = time;

        gantt.push_back({current.pid, start, time});
    }

    calculateMetrics(p);
    return p;
}
