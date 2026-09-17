#include "Deadlock.h"
#include <algorithm>

bool DeadlockDetector::bankersAlgorithm(
    const std::vector<std::vector<int>>& allocation,
    const std::vector<std::vector<int>>& maximum,
    const std::vector<int>& available,
    std::vector<int>& safeSequence) {

    const int n = static_cast<int>(allocation.size());
    if (n == 0 || maximum.size() != allocation.size())
        return false;

    const int m = static_cast<int>(available.size());

    std::vector<std::vector<int>> need(n, std::vector<int>(m));

    for (int i = 0; i < n; ++i) {
        if (allocation[i].size() != static_cast<size_t>(m) ||
            maximum[i].size() != static_cast<size_t>(m))
            return false;

        for (int j = 0; j < m; ++j) {
            need[i][j] = maximum[i][j] - allocation[i][j];
            if (need[i][j] < 0)
                return false;
        }
    }

    std::vector<int> work = available;
    std::vector<bool> finish(n, false);

    safeSequence.clear();

    for (int count = 0; count < n; ++count) {
        bool found = false;

        for (int i = 0; i < n; ++i) {
            if (finish[i]) continue;

            bool canFinish = true;

            for (int j = 0; j < m; ++j) {
                if (need[i][j] > work[j]) {
                    canFinish = false;
                    break;
                }
            }

            if (!canFinish) continue;

            for (int j = 0; j < m; ++j)
                work[j] += allocation[i][j];

            finish[i] = true;
            safeSequence.push_back(i);
            found = true;
        }

        if (!found)
            break;
    }

    return static_cast<int>(safeSequence.size()) == n;
}
