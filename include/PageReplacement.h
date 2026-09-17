#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H

#include <vector>

struct PageResult {
    int pageFaults;
    int pageHits;
};

// Static utility class (no per-instance state needed) implementing three
// classic page-replacement algorithms for a given reference string and
// number of physical frames.
class PageReplacement {
public:
    static PageResult fifo(const std::vector<int>& referenceString, int frameCount);
    static PageResult lru(const std::vector<int>& referenceString, int frameCount);
    static PageResult optimal(const std::vector<int>& referenceString, int frameCount);
};

#endif
