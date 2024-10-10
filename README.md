# Algorithms and Principles of Informatics Project - 2021

Algorithms and Principles of Informatics Project - Politecnico di Milano - Academic Year 2020/2021

## Overview

This project, developed as part of a course at POLIMI, implements a Red-Black Tree and Dijkstra's algorithm to efficiently find the shortest paths in a directed, weighted graph. The program is designed to read input from standard input, process the data, and perform various operations, including insertion into the Red-Black Tree and heap operations for Dijkstra's algorithm.

**Final grade**: $30/30\ cum\ laude$

### Key Features

- **Red-Black Tree**: Efficiently manages a dynamic set of nodes for the graph, providing O(log n) time complexity for insertion and deletion operations. It ensures that the tree remains balanced, which is critical for maintaining performance.
- **Dijkstra's Algorithm**: Calculates the shortest paths from a source node to all other nodes in the graph. The algorithm is implemented using a priority queue for efficient extraction of the minimum distance node.
- **Min-Heap**: Utilized within Dijkstra's algorithm to efficiently manage and retrieve the next node to process based on the shortest path estimate, enhancing the performance of the algorithm.
- **Optimized I/O**: Utilizes `getchar_unlocked` for faster input operations, significantly improving performance for larger datasets.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Algorithm Description](#algorithm-description)
- [Makefile Commands](#makefile-commands)
- [Project Description](#project-description-graphranker)

## Installation

To compile the project, ensure you have GCC installed on your system. Clone this repository and navigate into it. Run the following command:

```bash
make
```

This will generate the executable file named `executable`.

Come testcase are zipped

```bash
cat private/input/inputs_part_* > private/input/inputs.tar.bz2
tar -xvjf private/input/inputs.tar.bz2
```

## Usage

To run the program, provide input through standard input. The input format must adhere to the specifications for Dijkstra's algorithm and the Red-Black Tree.

```bash
./executable < input.txt
```

Where `input.txt` contains the graph representation and source node information.

## Algorithm Description

### Red-Black Tree

The Red-Black Tree implementation maintains the properties of a balanced binary search tree, ensuring O(log n) time complexity for insertion and deletion operations. The main functions include:

- **Insertion**: Nodes are inserted while maintaining the color properties of the tree, ensuring that no two consecutive red nodes exist, and that the tree remains approximately balanced.
- **Rotations**: Left and right rotations are performed to maintain balance during insertion and deletion.

### Dijkstra's Algorithm

Dijkstra's algorithm finds the shortest paths from a starting node to all other nodes in a graph. The implementation includes:

- A **min-heap** (priority queue) for efficient retrieval of the next node to process, enabling O(log n) time complexity for inserting and extracting the minimum element. This is crucial for optimizing the algorithm, especially in dense graphs.
- An **adjacency matrix** to represent the graph, allowing for quick access to edge weights.
- The algorithm updates distances and the heap as shorter paths are discovered, ensuring the shortest path to each node is computed.

### Min Heap

The **min-heap** is a critical data structure used in the Dijkstra's algorithm implementation to manage the nodes that need to be processed based on their current shortest path estimate. The min-heap allows for:

- **Efficient Extraction**: The node with the smallest distance can be extracted in O(log n) time, which is essential for iterating through nodes in order of their distance from the source.
- **Dynamic Updates**: As shorter paths to nodes are found, the distances in the heap can be updated efficiently. The decrease-key operation is implemented to maintain the heap's properties.

This ensures that the algorithm can efficiently handle updates and continue to find the shortest paths across various iterations.

## Makefile Commands

The Makefile includes several commands for building, testing, and cleaning the project:

- `make`: Compiles the project and generates the executable.
- `make clean`: Removes the compiled executable and temporary files.
- `make test_open`: Runs tests for open cases.
- `make test_private`: Runs tests for private cases.
- `make test_all`: Runs all tests (open and private).
- `make valgrind`: Checks for memory leaks using Valgrind.
- `make callgrind`: Profiles the program execution with Callgrind.

## Project Description: GraphRanker

**GraphRanker** is a project aimed at managing a ranking system for directed, weighted graphs. The program keeps track of the top \( k \) "best" graphs based on a specified metric.

### Input Specifications

The program expects the following input:

1. Two parameters on the first line of the input file, separated by space:
   - **d**: The number of nodes in the graphs.
   - **k**: The length of the ranking list.

2. A sequence of commands:
   - **AddGraph [adjacency-matrix]**: This command requests the addition of a graph to the ranking system. It is followed by the adjacency matrix of the graph, printed one line for each row with elements separated by commas. The nodes of the graph are logically labeled with an integer index from \( 0 \) to \( d-1 \). The weights of the graph's edges are integers in the range \([0, 2^{32} - 1]\).

   Example for \( d=3 \):

   ```txt
   AddGraph
   3,7,42
   0,7,2
   7,4,3
   ```

3. **TopK**: This command requests the program to print the indices of the \( k \) graphs with the smallest values of the following metric:
   - The sum of the shortest paths from node \( 0 \) to all other nodes in the graph.

If multiple graphs have the same metric value, the program prioritizes the earlier graphs. The indices are printed on a single line, separated by spaces, in any order.

### Example Execution

For an input of:

```txt
3 2
AddGraph
0,4,3
0,2,0
2,0,0
AddGraph
0,0,2
7,0,4
0,1,0
AddGraph
3,1,8
0,0,5
0,9,0
TopK
```

The output will indicate:

- The addition of the first graph (index 0, shortest path sum = 7).
- The addition of the second graph (index 1, shortest path sum = 5).
- The addition of the third graph (index 2, shortest path sum = 7).
- Finally, the command `TopK` may output `0 1` or `1 0`, indicating the indices of the top \( k \) graphs.
