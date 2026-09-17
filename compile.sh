#!/bin/bash
# Quick compile without needing CMake.
g++ -std=c++17 -Wall -Iinclude main.cpp src/*.cpp -o os_sim
echo "Build complete. Run with: ./os_sim"
