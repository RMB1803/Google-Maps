# Dijkstra's Shortest Path Algorithm: City Map Simulator

This is a simple, terminal-based C++ program created for a Design and Analysis of Algorithms (DAA) course project.

## Problem Statement

The goal of this project is to implement Dijkstra's algorithm to find the shortest path between two nodes in a graph. The program simulates a core feature of applications like Google Maps, where a user can input a "source" and "destination" city and receive the shortest possible route and total distance.

The implementation is designed to run in a terminal and emphasizes the core logic of the algorithm over a complex user interface.

## How to Compile & Run

1.  **Save the file:** Ensure you have the `dijkstra_simple.cpp` file on your system.

2.  **Compile:** Open your terminal and navigate to the directory where you saved the file. Use `g++` to compile it:

    ```bash
    g++ -o dijkstra dijkstra_simple.cpp -std=c++11
    ```

    *(The `-std=c++11` flag ensures compatibility, though it may compile without it).*

3.  **Run:** Execute the compiled program:

    ```bash
    ./dijkstra
    ```

## How It Works: The Algorithm

This program implements Dijkstra's algorithm using an adjacency matrix and three simple arrays.

### 1. Graph Representation

* **Adjacency Matrix (`graph[][]`):** The map is stored in a 2D array, `int graph[NUM_CITIES][NUM_CITIES]`. The value at `graph[i][j]` holds the "weight" (distance) of the road from city `i` to city `j`.
* **Infinity (`INF`):** A constant `INF` (the maximum possible integer) is used to represent "no direct path" between two cities.
* **City Mapping (`cities[]`):** A `string` array maps city names (e..g., "Mumbai") to their corresponding index in the matrix (e.g., `0`).

### 2. Core Data Structures

The algorithm's entire state is managed by three arrays:

* `int dist[]`: Stores the **shortest distance** found *so far* from the source to every other city. It is initialized to `INF` for all cities except the source, which is `0`.
* `bool visited[]`: Tracks which nodes have been finalized. A node is marked `true` when we are *certain* we have found the absolute shortest path to it.
* `int prev[]`: Stores the **predecessor** of each node in the shortest path. This array acts as a "trail of breadcrumbs" to reconstruct the path after the algorithm finishes.

### 3. Algorithm Steps in the Code

The `dijkstra()` function executes the algorithm in these phases:

1.  **Initialization:** The `dist`, `visited`, and `prev` arrays are initialized as described above. The source's distance is set to `0`.
2.  **Main Loop:** The algorithm loops `NUM_CITIES` times. In each loop, it performs two key operations:
    * **A. Select Node:** The `findMinDistanceNode()` function scans the `dist[]` array to find the **unvisited** node (`u`) with the **smallest distance**. This is a simple `O(V)` substitute for a priority queue's `O(log V)` operation.
    * **B. Visit Node:** The selected node `u` is marked as `visited[u] = true`. Its distance `dist[u]` is now considered final and will not change.
3.  **Relaxation:** After visiting `u`, the code loops through all its neighbors (`v`). For each neighbor, it performs the **relaxation check**:
    * `if (dist[u] + graph[u][v] < dist[v])`
    * This `if` statement asks: "Is the path from the source *through `u`* to get to `v` **shorter** than the current best path we know for `v`?"
    * If **YES**, it updates `dist[v]` with the new, shorter distance and sets `prev[v] = u`, marking `u` as the new best predecessor for `v`.
4.  **Termination:** The loop finishes after all reachable nodes have been visited. The `dist[]` array now contains the shortest distance from the source to all other nodes, and the `prev[]` array contains the shortest path tree.
5.  **Path Reconstruction:** The `printPath()` function follows the `prev[]` array backward (from destination to source) to build the human-readable path.

## The Map (Graph Data)

The hardcoded graph is defined in the `main()` function.

**Cities (Nodes):**

* `0`: Mumbai
* `1`: Delhi
* `2`: Jaipur
* `3`: Kolkata
* `4.`: Chennai
* `5`: Bengaluru

**Distances (Edges / Adjacency Matrix):**

```cpp
int graph[NUM_CITIES][NUM_CITIES] = {
      // M(0)  D(1)   J(2)   K(3)   C(4)   B(5)
        {0,   1400,   950,     0,   1350,  1000}, // 0: Mumbai
        {1400,   0,   270,   1500,    0,   2150}, // 1: Delhi
        {950,   270,    0,   1600,  2100,  2000}, // 2: Jaipur
        {0,    1500,  1600,    0,   1650,  1900}, // 3: Kolkata
        {1350,   0,   2100,  1650,    0,   350}, // 4: Chennai
        {1000, 2150,  2000,  1900,   350,    0}  // 5: Bengaluru
};
