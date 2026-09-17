#include "../include/Scheduler.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void Scheduler::printGanttChart(const std::vector<GanttEntry>& chart) const {
    std::cout << "\nGantt Chart:\n| ";
    for (const auto& e : chart) {
        std::cout << "P" << e.pid << " (" << e.start << "-" << e.end << ") | ";
    }
    std::cout << "\n";
}

void Scheduler::printMetricsTable(const std::vector<Process>& processes) const {
    std::vector<Process> sorted = processes;
    std::sort(sorted.begin(), sorted.end(),
              [](const Process& a, const Process& b) { return a.pid < b.pid; });

    std::cout << "\n"
              << std::left
              << std::setw(8) << "PID"
              << std::setw(8) << "AT"
              << std::setw(8) << "BT"
              << std::setw(8) << "CT"
              << std::setw(8) << "TAT"
              << std::setw(8) << "WT"
              << std::setw(8) << "RT" << "\n";

    for (const auto& p : sorted) {
        std::cout << std::left
                  << std::setw(8) << p.pid
                  << std::setw(8) << p.arrivalTime
                  << std::setw(8) << p.burstTime
                  << std::setw(8) << p.completionTime
                  << std::setw(8) << p.turnaroundTime
                  << std::setw(8) << p.waitingTime
                  << std::setw(8) << p.responseTime << "\n";
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nAverage Waiting Time    : " << averageWaitingTime(processes) << "\n";
    std::cout << "Average Turnaround Time : " << averageTurnaroundTime(processes) << "\n";
    std::cout << "Average Response Time   : " << averageResponseTime(processes) << "\n";
}

double Scheduler::averageWaitingTime(const std::vector<Process>& processes) const {
    double total = 0;
    for (const auto& p : processes) total += p.waitingTime;
    return processes.empty() ? 0.0 : total / processes.size();
}

double Scheduler::averageTurnaroundTime(const std::vector<Process>& processes) const {
    double total = 0;
    for (const auto& p : processes) total += p.turnaroundTime;
    return processes.empty() ? 0.0 : total / processes.size();
}

double Scheduler::averageResponseTime(const std::vector<Process>& processes) const {
    double total = 0;
    for (const auto& p : processes) total += p.responseTime;
    return processes.empty() ? 0.0 : total / processes.size();
}
