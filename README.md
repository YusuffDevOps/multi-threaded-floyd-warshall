# Multi-threaded Floyd-Warshall Algorithm

## Overview
This project implements the **Floyd-Warshall algorithm** to find the shortest paths between all pairs of nodes in a weighted graph. It includes both **single-threaded** and **multi-threaded** versions to compare performance and efficiency. 

The multi-threaded version uses **POSIX threads (pthreads)** and **semaphores** to parallelize the shortest path calculations.

## Features
- Implements **single-threaded** and **multi-threaded** Floyd-Warshall algorithms.
- Uses **pthreads and semaphores** for multi-threaded execution.
- Reads graph input from a file (`graph.txt`).
- Compares runtime performance between single-threaded and multi-threaded implementations.
- Includes Python scripts for **automated testing and runtime evaluation**.

## Files
| File | Description |
|------|------------|
| `multiFW.c` | Multi-threaded implementation of the Floyd-Warshall algorithm |
| `singleFW.c` | Single-threaded implementation for comparison |
| `graph.txt` | Input file containing the graph (nodes, edges, weights) |
| `scripts.py` | Python script for generating test cases and benchmarking runtime |
| `Project Report.docx` | Detailed analysis and performance evaluation |

## Algorithm
1. **Read the graph input** from `graph.txt`.
2. **Initialize the adjacency matrix** with edge weights (or infinity for no edges).
3. **Run Floyd-Warshall Algorithm**:
   - **Single-threaded version**: Iterates through nodes sequentially.
   - **Multi-threaded version**: Uses **pthreads** to parallelize computation across multiple threads.
4. **Print the shortest path matrix**.

## Usage

### **Compiling the Single-threaded Version**
```sh
gcc singleFW.c -o singleFW
```
### **Compiling the Multi-threaded Version**
```sh
gcc multiFW.c -o multiFW
```

System Requirements
GCC Compiler (for C programs)
POSIX Threads (pthreads) Support
Python3 (for running scripts)
Linux/macOS/WSL recommended for execution
