#include "Scheduler.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>

void Scheduler::calculateMetrics(std::vector<Process>& processes) {
    for (auto& p : processes) {
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
    }
}

void Scheduler::printGantt(const std::vector<GanttEntry>& gantt) {
    if (gantt.empty()) return;

    std::cout << "\nGantt Chart\n";
    std::cout << " ";
    for (const auto& e : gantt) {
        std::cout << "--------";
    }
    std::cout << "-\n|";

    for (const auto& e : gantt) {
        std::cout << " " << std::setw(6) << std::left << e.pid << "|";
    }
    std::cout << "\n ";

    for (const auto& e : gantt) {
        std::cout << "--------";
    }
    std::cout << "-\n";

    std::cout << gantt.front().start;
    for (const auto& e : gantt) {
        std::cout << std::setw(9) << e.end;
    }
    std::cout << "\n";
}

void Scheduler::printResults(const std::vector<Process>& processes,
                             const std::vector<GanttEntry>& gantt) {
    printGantt(gantt);

    std::cout << "\nProcess Results\n";
    std::cout << std::left
              << std::setw(10) << "PID"
              << std::setw(8) << "AT"
              << std::setw(8) << "BT"
              << std::setw(8) << "PR"
              << std::setw(8) << "CT"
              << std::setw(8) << "TAT"
              << std::setw(8) << "WT"
              << std::setw(8) << "RT"
              << "\n";

    double totalWT = 0, totalTAT = 0, totalRT = 0;

    for (const auto& p : processes) {
        std::cout << std::left
                  << std::setw(10) << p.pid
                  << std::setw(8) << p.arrivalTime
                  << std::setw(8) << p.burstTime
                  << std::setw(8) << p.priority
                  << std::setw(8) << p.completionTime
                  << std::setw(8) << p.turnaroundTime
                  << std::setw(8) << p.waitingTime
                  << std::setw(8) << p.responseTime
                  << "\n";

        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
        totalRT += p.responseTime;
    }

    if (!processes.empty()) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\nAverage Waiting Time    : "
                  << totalWT / processes.size() << "\n";
        std::cout << "Average Turnaround Time : "
                  << totalTAT / processes.size() << "\n";
        std::cout << "Average Response Time   : "
                  << totalRT / processes.size() << "\n";
    }
}
