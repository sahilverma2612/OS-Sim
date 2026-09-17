#include "../include/DeadlockDetector.h"

// Standard Banker's safety algorithm:
// 1. Compute Need[i][j] = Max[i][j] - Allocation[i][j] for every process/resource.
// 2. Repeatedly find a process whose Need can be satisfied by the currently
//    available resources (Work). If found, pretend it finishes and releases
//    its allocation back into Work; add it to the safe sequence.
// 3. If we get through all n processes this way, the system is in a safe
//    state. If we get stuck (no process can proceed) before finishing all
//    of them, the state is unsafe -- a deadlock is possible.
// Time complexity: O(n^2 * m) where n = processes, m = resource types.
bool DeadlockDetector::isSafe(
    const std::vector<int>& available,
    const std::vector<std::vector<int>>& allocation,
    const std::vector<std::vector<int>>& maxDemand,
    std::vector<int>& safeSequence
) {
    int n = (int)allocation.size();
    int m = (int)available.size();

    std::vector<std::vector<int>> need(n, std::vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxDemand[i][j] - allocation[i][j];

    std::vector<int> work = available;
    std::vector<bool> finished(n, false);
    safeSequence.clear();

    int count = 0;
    while (count < n) {
        bool foundProcess = false;
        for (int i = 0; i < n; i++) {
            if (finished[i]) continue;

            bool canRun = true;
            for (int j = 0; j < m; j++) {
                if (need[i][j] > work[j]) { canRun = false; break; }
            }

            if (canRun) {
                for (int j = 0; j < m; j++) work[j] += allocation[i][j];
                finished[i] = true;
                safeSequence.push_back(i);
                foundProcess = true;
                count++;
            }
        }
        if (!foundProcess) break;  // stuck -- no process can proceed
    }

    return count == n;
}
