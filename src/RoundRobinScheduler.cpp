#include "../include/RoundRobinScheduler.h"
#include <queue>
#include <algorithm>

// Uses a queue<int> (process indices) as the ready queue -- this is the
// textbook use case for a queue in an OS context: fair, cyclic access to
// the CPU. Each process gets at most `quantum` time units per turn; if it
// isn't done, it goes to the back of the queue.
// Time complexity: O(n * burstTime / quantum) in the worst case, since each
// process may need multiple turns through the queue.
std::vector<GanttEntry> RoundRobinScheduler::schedule(std::vector<Process>& processes) {
    std::vector<GanttEntry> chart;
    int n = processes.size();
    for (auto& p : processes) p.remainingTime = p.burstTime;

    std::vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        return processes[a].arrivalTime < processes[b].arrivalTime;
    });

    std::queue<int> readyQueue;
    int currentTime = 0;
    int completed = 0;
    int arrivalPtr = 0;

    auto enqueueArrivals = [&](int uptoTime) {
        while (arrivalPtr < n && processes[order[arrivalPtr]].arrivalTime <= uptoTime) {
            readyQueue.push(order[arrivalPtr]);
            arrivalPtr++;
        }
    };

    enqueueArrivals(currentTime);

    while (completed < n) {
        if (readyQueue.empty()) {
            if (arrivalPtr < n) {
                currentTime = processes[order[arrivalPtr]].arrivalTime;
                enqueueArrivals(currentTime);
            } else {
                break;
            }
        }

        int idx = readyQueue.front();
        readyQueue.pop();
        Process& p = processes[idx];

        if (p.responseTime == -1) p.responseTime = currentTime - p.arrivalTime;

        int execTime = std::min(quantum, p.remainingTime);
        int start = currentTime;
        currentTime += execTime;
        p.remainingTime -= execTime;
        chart.push_back({p.pid, start, currentTime});

        enqueueArrivals(currentTime);  // new arrivals join the queue before the current process re-joins

        if (p.remainingTime > 0) {
            readyQueue.push(idx);
        } else {
            p.completionTime = currentTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            completed++;
        }
    }
    return chart;
}
