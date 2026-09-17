#ifndef DEADLOCK_DETECTOR_H
#define DEADLOCK_DETECTOR_H

#include <vector>

// Implements the Banker's Algorithm safety check: given the available
// resources and each process's current allocation and maximum demand,
// determine whether a "safe sequence" exists in which all processes could
// finish without deadlock.
class DeadlockDetector {
public:
    static bool isSafe(
        const std::vector<int>& available,
        const std::vector<std::vector<int>>& allocation,
        const std::vector<std::vector<int>>& maxDemand,
        std::vector<int>& safeSequence
    );
};

#endif
