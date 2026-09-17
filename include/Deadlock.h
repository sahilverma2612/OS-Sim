#pragma once
#include <vector>

class DeadlockDetector {
public:
    // Returns true when a safe sequence exists.
    static bool bankersAlgorithm(
        const std::vector<std::vector<int>>& allocation,
        const std::vector<std::vector<int>>& maximum,
        const std::vector<int>& available,
        std::vector<int>& safeSequence);
};
