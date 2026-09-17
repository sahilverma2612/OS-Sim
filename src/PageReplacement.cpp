#include "../include/PageReplacement.h"
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <climits>

// FIFO: evict the page that has been in memory the longest, regardless of
// how recently it was used. Simple, but can suffer from Belady's Anomaly
// (more frames can sometimes cause MORE faults).
PageResult PageReplacement::fifo(const std::vector<int>& ref, int frameCount) {
    std::vector<int> frames;
    std::queue<int> insertionOrder;
    int faults = 0, hits = 0;

    for (int page : ref) {
        bool present = std::find(frames.begin(), frames.end(), page) != frames.end();
        if (present) {
            hits++;
            continue;
        }
        faults++;
        if ((int)frames.size() < frameCount) {
            frames.push_back(page);
            insertionOrder.push(page);
        } else {
            int victim = insertionOrder.front();
            insertionOrder.pop();
            *std::find(frames.begin(), frames.end(), victim) = page;
            insertionOrder.push(page);
        }
    }
    return {faults, hits};
}

// LRU: evict the page that was used least recently. Requires tracking the
// last-access time of every page currently in memory.
PageResult PageReplacement::lru(const std::vector<int>& ref, int frameCount) {
    std::vector<int> frames;
    std::unordered_map<int, int> lastUsed;
    int faults = 0, hits = 0;

    for (int t = 0; t < (int)ref.size(); t++) {
        int page = ref[t];
        bool present = std::find(frames.begin(), frames.end(), page) != frames.end();

        if (present) {
            hits++;
        } else {
            faults++;
            if ((int)frames.size() < frameCount) {
                frames.push_back(page);
            } else {
                int victim = frames[0];
                int oldestTime = lastUsed[victim];
                for (int f : frames) {
                    if (lastUsed[f] < oldestTime) {
                        oldestTime = lastUsed[f];
                        victim = f;
                    }
                }
                *std::find(frames.begin(), frames.end(), victim) = page;
            }
        }
        lastUsed[page] = t;
    }
    return {faults, hits};
}

// Optimal (Belady's algorithm): evict the page whose next use is farthest
// in the future (or never used again). Not implementable in a real OS
// (requires knowing the future) but used as the theoretical best-case
// baseline to compare FIFO/LRU against.
PageResult PageReplacement::optimal(const std::vector<int>& ref, int frameCount) {
    std::vector<int> frames;
    int faults = 0, hits = 0;

    for (int t = 0; t < (int)ref.size(); t++) {
        int page = ref[t];
        bool present = std::find(frames.begin(), frames.end(), page) != frames.end();

        if (present) {
            hits++;
            continue;
        }
        faults++;
        if ((int)frames.size() < frameCount) {
            frames.push_back(page);
        } else {
            int victimPos = 0;
            int farthestUse = -1;
            for (int i = 0; i < (int)frames.size(); i++) {
                int nextUse = INT_MAX;
                for (int j = t + 1; j < (int)ref.size(); j++) {
                    if (ref[j] == frames[i]) { nextUse = j; break; }
                }
                if (nextUse > farthestUse) {
                    farthestUse = nextUse;
                    victimPos = i;
                }
            }
            frames[victimPos] = page;
        }
    }
    return {faults, hits};
}
