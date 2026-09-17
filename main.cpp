#include <iostream>
#include <vector>
#include <iomanip>
#include "include/Process.h"
#include "include/Scheduler.h"
#include "include/FCFSScheduler.h"
#include "include/SJFScheduler.h"
#include "include/SRTFScheduler.h"
#include "include/RoundRobinScheduler.h"
#include "include/PriorityScheduler.h"
#include "include/PageReplacement.h"
#include "include/DeadlockDetector.h"

using namespace std;

vector<Process> inputProcesses() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 1; i <= n; i++) {
        int at, bt, pr;
        cout << "\nProcess P" << i << "\n";
        cout << "  Arrival Time: ";
        cin >> at;
        cout << "  Burst Time: ";
        cin >> bt;
        cout << "  Priority (lower number = higher priority, enter 0 if unused): ";
        cin >> pr;
        processes.emplace_back(i, at, bt, pr);
    }
    return processes;
}

// Takes a Scheduler& (base class reference) -- this works for ANY derived
// scheduler thanks to runtime polymorphism. This function doesn't need to
// know or care whether it's running FCFS, SJF, or Round Robin.
void runScheduler(Scheduler& scheduler, vector<Process> processes) {
    cout << "\n=== " << scheduler.name() << " ===\n";
    auto chart = scheduler.schedule(processes);
    scheduler.printGanttChart(chart);
    scheduler.printMetricsTable(processes);
}

void compareAllAlgorithms(const vector<Process>& original) {
    cout << "\n" << left
         << setw(20) << "Algorithm"
         << setw(15) << "Avg WT"
         << setw(15) << "Avg TAT" << "\n";
    cout << fixed << setprecision(2);

    FCFSScheduler fcfs;
    vector<Process> p1 = original;
    fcfs.schedule(p1);
    cout << left << setw(20) << "FCFS"
         << setw(15) << fcfs.averageWaitingTime(p1)
         << setw(15) << fcfs.averageTurnaroundTime(p1) << "\n";

    SJFScheduler sjf;
    vector<Process> p2 = original;
    sjf.schedule(p2);
    cout << left << setw(20) << "SJF"
         << setw(15) << sjf.averageWaitingTime(p2)
         << setw(15) << sjf.averageTurnaroundTime(p2) << "\n";

    SRTFScheduler srtf;
    vector<Process> p3 = original;
    srtf.schedule(p3);
    cout << left << setw(20) << "SRTF"
         << setw(15) << srtf.averageWaitingTime(p3)
         << setw(15) << srtf.averageTurnaroundTime(p3) << "\n";

    int q;
    cout << "Enter Time Quantum for Round Robin: ";
    cin >> q;
    RoundRobinScheduler rr(q);
    vector<Process> p4 = original;
    rr.schedule(p4);
    cout << left << setw(20) << "Round Robin"
         << setw(15) << rr.averageWaitingTime(p4)
         << setw(15) << rr.averageTurnaroundTime(p4) << "\n";

    PriorityScheduler prio;
    vector<Process> p5 = original;
    prio.schedule(p5);
    cout << left << setw(20) << "Priority"
         << setw(15) << prio.averageWaitingTime(p5)
         << setw(15) << prio.averageTurnaroundTime(p5) << "\n";
}

void cpuSchedulingMenu() {
    vector<Process> processes = inputProcesses();
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "          CPU SCHEDULING\n";
        cout << "====================================\n";
        cout << "1. FCFS\n";
        cout << "2. SJF (Non-preemptive)\n";
        cout << "3. SRTF (Preemptive)\n";
        cout << "4. Round Robin\n";
        cout << "5. Priority Scheduling\n";
        cout << "6. Compare All Algorithms\n";
        cout << "7. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: { FCFSScheduler s; runScheduler(s, processes); break; }
            case 2: { SJFScheduler s; runScheduler(s, processes); break; }
            case 3: { SRTFScheduler s; runScheduler(s, processes); break; }
            case 4: {
                int q;
                cout << "Enter Time Quantum: ";
                cin >> q;
                RoundRobinScheduler s(q);
                runScheduler(s, processes);
                break;
            }
            case 5: { PriorityScheduler s; runScheduler(s, processes); break; }
            case 6: compareAllAlgorithms(processes); break;
            case 7: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 7);
}

void pageReplacementMenu() {
    int n;
    cout << "Enter length of reference string: ";
    cin >> n;

    vector<int> ref(n);
    cout << "Enter reference string (space-separated page numbers): ";
    for (int i = 0; i < n; i++) cin >> ref[i];

    int frames;
    cout << "Enter number of frames: ";
    cin >> frames;

    auto fifoResult = PageReplacement::fifo(ref, frames);
    auto lruResult = PageReplacement::lru(ref, frames);
    auto optResult = PageReplacement::optimal(ref, frames);

    cout << "\n" << left
         << setw(15) << "Algorithm"
         << setw(15) << "Page Faults"
         << setw(15) << "Page Hits" << "\n";
    cout << left << setw(15) << "FIFO"    << setw(15) << fifoResult.pageFaults << setw(15) << fifoResult.pageHits << "\n";
    cout << left << setw(15) << "LRU"     << setw(15) << lruResult.pageFaults  << setw(15) << lruResult.pageHits  << "\n";
    cout << left << setw(15) << "Optimal" << setw(15) << optResult.pageFaults  << setw(15) << optResult.pageHits  << "\n";
}

void deadlockDetectionMenu() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<int> available(m);
    cout << "Enter available resources (" << m << " values): ";
    for (int i = 0; i < m; i++) cin >> available[i];

    vector<vector<int>> allocation(n, vector<int>(m));
    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process P" << i << " (" << m << " values): ";
        for (int j = 0; j < m; j++) cin >> allocation[i][j];
    }

    vector<vector<int>> maxDemand(n, vector<int>(m));
    cout << "\nEnter Max Demand Matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process P" << i << " (" << m << " values): ";
        for (int j = 0; j < m; j++) cin >> maxDemand[i][j];
    }

    vector<int> safeSequence;
    bool safe = DeadlockDetector::isSafe(available, allocation, maxDemand, safeSequence);

    if (safe) {
        cout << "\nSystem Status: SAFE\n";
        cout << "Safe Sequence: ";
        for (size_t i = 0; i < safeSequence.size(); i++) {
            cout << "P" << safeSequence[i];
            if (i != safeSequence.size() - 1) cout << " -> ";
        }
        cout << "\n";
    } else {
        cout << "\nSystem Status: UNSAFE (deadlock possible)\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n====================================\n";
        cout << "       OPERATING SYSTEM SIMULATOR\n";
        cout << "====================================\n";
        cout << "1. CPU Scheduling\n";
        cout << "2. Page Replacement\n";
        cout << "3. Deadlock Detection (Banker's Algorithm)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: cpuSchedulingMenu(); break;
            case 2: pageReplacementMenu(); break;
            case 3: deadlockDetectionMenu(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
