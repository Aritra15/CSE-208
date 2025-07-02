# Data Structures and Algorithms Implementation

This repository contains implementations of various data structures and algorithms in C++.

## Table of Contents

- [All Pairs Shortest Path (APSP)](#all-pairs-shortest-path-apsp)
- [Fibonacci Heap](#fibonacci-heap)
- [Hashing](#hashing)
- [Maximum Flow](#maximum-flow)
- [Minimum Spanning Tree (MST)](#minimum-spanning-tree-mst)
- [Red-Black Tree](#red-black-tree)
- [Single-Source Shortest Path (SSSP)](#single-source-shortest-path-sssp)

## All Pairs Shortest Path (APSP)

Implementation of algorithms to find shortest paths between all pairs of vertices in a graph.
- Floyd-Warshall algorithm

## Fibonacci Heap

Implementation of a Fibonacci Heap data structure that supports the following operations:
- Insert
- Extract-Max
- Increase-Key
- Delete
- Meld (combining two heaps)

## Hashing

Various hashing techniques implemented:
- Custom hashing
- Double hashing
- Separate chaining

## Maximum Flow

Algorithms to find maximum flow in a network:
- Ford-Fulkerson algorithm

## Minimum Spanning Tree (MST)

Implementation of algorithms to find minimum spanning trees in graphs:
- Kruskal's algorithm
- Prim's algorithm
- Disjoint Set data structure for efficient implementation

## Red-Black Tree

Self-balancing binary search tree implementation with the following operations:
- Insert
- Delete
- Search

## Single-Source Shortest Path (SSSP)

Algorithms for finding shortest paths from a source vertex to all other vertices:
- Dijkstra's algorithm
- Bellman-Ford algorithm
- Bidirectional Dijkstra's algorithm

## Build Instructions

To compile any of the programs, navigate to its directory and use g++:

```bash
g++ -o program_name file_name.cpp
```

For example:

```bash
g++ -o fibonacci_heap fibonacciHeap.cpp
```

## Usage

Run the executable file after compilation:

```bash
./program_name
```

Or on Windows:

```bash
program_name.exe
```

## Requirements

- C++ compiler (supporting C++11 or later)
- Standard Template Library (STL)
