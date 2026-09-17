# OS-Sim — Operating System Scheduling & Memory Management Simulator

A C++ console application simulating core Operating System concepts:
CPU scheduling algorithms, page replacement algorithms, and deadlock
detection via the Banker's Algorithm.

Built with OOP principles (abstraction, inheritance, polymorphism,
encapsulation) so it doubles as your OOP interview talking point, not
just an OS one.

## Features

**1. CPU Scheduling**
- FCFS (First Come First Serve)
- SJF (Shortest Job First — non-preemptive)
- SRTF (Shortest Remaining Time First — preemptive)
- Round Robin (configurable time quantum)
- Priority Scheduling (non-preemptive)
- Compare All Algorithms (side-by-side avg waiting/turnaround time)

Each algorithm prints a Gantt chart and a metrics table (Completion
Time, Turnaround Time, Waiting Time, Response Time) plus averages.

**2. Page Replacement**
- FIFO
- LRU (Least Recently Used)
- Optimal (Belady's Algorithm)

Reports page faults and page hits for a given reference string and
frame count.

**3. Deadlock Detection**
- Banker's Algorithm safety check
- Given Available, Allocation, and Max Demand matrices, determines if
  a safe sequence exists.

## How to Build & Run

### Option A — one-line compile (no dependencies)
```bash
chmod +x compile.sh
./compile.sh
./os_sim
```

### Option B — using CMake
```bash
mkdir build && cd build
cmake ..
make
./os_sim
```

### Option C — manual g++
```bash
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o os_sim
./os_sim
```

## Project Structure

```
OS-Sim/
├── include/              # Header files (class declarations)
│   ├── Process.h
│   ├── Scheduler.h       # Abstract base class
│   ├── FCFSScheduler.h
│   ├── SJFScheduler.h
│   ├── SRTFScheduler.h
│   ├── RoundRobinScheduler.h
│   ├── PriorityScheduler.h
│   ├── PageReplacement.h
│   └── DeadlockDetector.h
├── src/                  # Implementation files
│   ├── Process.cpp
│   ├── Scheduler.cpp
│   ├── FCFSScheduler.cpp
│   ├── SJFScheduler.cpp
│   ├── SRTFScheduler.cpp
│   ├── RoundRobinScheduler.cpp
│   ├── PriorityScheduler.cpp
│   ├── PageReplacement.cpp
│   └── DeadlockDetector.cpp
├── main.cpp              # Menu-driven entry point
├── CMakeLists.txt
├── compile.sh
└── README.md
```

## OOP Design — Be Ready to Explain This

`Scheduler` is an **abstract base class** with one pure virtual method,
`schedule()`. Every algorithm (`FCFSScheduler`, `SJFScheduler`, etc.)
**inherits** from it and provides its own implementation — that's
**runtime polymorphism**: `main.cpp` calls `scheduler.schedule(...)`
through a base-class reference without knowing which concrete
algorithm it's running.

Shared logic (printing the Gantt chart, computing averages) lives once
in the base class instead of being duplicated in every subclass —
that's the point of putting it there rather than in each derived
class.

`Process` **encapsulates** all of a process's state (arrival time,
burst time, computed metrics) behind a single object instead of
scattering parallel arrays everywhere.

`PageReplacement` and `DeadlockDetector` are static utility classes —
they hold no per-instance state, so there's no reason to instantiate
them; the algorithms are pure functions of their inputs.

## Likely Interview Follow-Ups (practice explaining these out loud)

**OOP:**
- Why is `Scheduler` abstract instead of a regular base class?
- What would break if `schedule()` weren't virtual?
- Why does `RoundRobinScheduler` need a constructor while the others don't?
- Could you use composition instead of inheritance here? What would you lose?

**OS — Scheduling:**
- Why can SJF/SRTF cause starvation? How would you fix it? (Aging)
- Why is Round Robin's performance sensitive to quantum size? What
  happens if quantum is too small or too large?
- Walk through why SRTF's average waiting time is typically lower than SJF's.
- What's the difference between turnaround time and response time, and why do both matter?

**OS — Memory:**
- What is Belady's Anomaly and why does it apply to FIFO but not LRU/Optimal?
- Why is Optimal not implementable in a real OS?
- How does LRU approximate Optimal, and where does it fall short?

**OS — Deadlock:**
- What are the four necessary conditions for deadlock?
- What's the difference between deadlock *detection* (what this
  project does) and deadlock *avoidance*/*prevention*?
- Why does Banker's Algorithm need to know the maximum demand in advance?

**Complexity:**
- FCFS: O(n log n) — dominated by the sort.
- SJF/Priority (this simple version): O(n²) — could be optimized to O(n log n) with a min-heap.
- SRTF/Round Robin: O(n × total burst time) — tick-by-tick simulation.
- Banker's safety check: O(n² × m).

## Possible Improvements (good answers to "what would you improve?")
- Replace the O(n²) SJF/Priority scan with a `priority_queue` for O(n log n).
- Add aging to Priority Scheduling to prevent starvation.
- Add multi-level feedback queue scheduling.
- Add a resource-request simulation (not just static matrices) for the deadlock module.
