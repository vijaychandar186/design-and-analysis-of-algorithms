# Design and Analysis of Algorithms

A collection of 15 lab exercises covering fundamental algorithm design paradigms, implemented in **C++17**.

## Labs Overview

| Lab | Topic | Algorithm(s) | Files |
|-----|-------|-------------|-------|
| 01 | Simple Algorithm | Insertion Sort | `insertion_sort.cpp` |
| 02 | Sorting | Bubble Sort | `bubble_sort.cpp` |
| 03 | Recurrence Type | Merge Sort, Linear Search | `merge_sort.cpp`, `linear_search.cpp` |
| 04 | Divide & Conquer | Quicksort, Binary Search | `quicksort.cpp`, `binary_search.cpp` |
| 05 | Matrix Multiply | Strassen's Algorithm | `strassen.cpp` |
| 06 | Divide & Conquer | Max/Min in Array, Convex Hull | `max_min.cpp`, `convex_hull.cpp` |
| 07 | Greedy | Huffman Coding, Fractional Knapsack | `huffman.cpp`, `knapsack_greedy.cpp` |
| 08 | Trees & Graphs | Tree Traversals, Kruskal's MST | `tree_traversals.cpp`, `kruskal.cpp` |
| 09 | Dynamic Programming | Longest Common Subsequence | `lcs.cpp` |
| 10 | Backtracking | N-Queens Problem | `n_queens.cpp` |
| 11 | Dynamic Programming | Travelling Salesman (Held-Karp) | `tsp.cpp` |
| 12 | Graph Traversal | BFS and DFS (Adjacency Matrix) | `bfs_dfs.cpp` |
| 13 | Randomised | Randomized Quicksort | `randomized_quicksort.cpp` |
| 14 | String Algorithms | Naive, KMP, Rabin-Karp | `string_matching.cpp` |
| 15 | Real-Time Problem | Job Scheduling with Deadlines | `job_scheduling.cpp` |

## Directory Structure

```
design-and-analysis-of-algorithms/
├── README.md
├── exercises/
│   ├── lab01_insertion_sort/
│   ├── lab02_bubble_sort/
│   ├── lab03_merge_sort_linear_search/
│   ├── lab04_quicksort_binary_search/
│   ├── lab05_strassen_matrix/
│   ├── lab06_max_min_convex_hull/
│   ├── lab07_huffman_knapsack/
│   ├── lab08_tree_traversals_kruskal/
│   ├── lab09_lcs/
│   ├── lab10_n_queens/
│   ├── lab11_tsp/
│   ├── lab12_bfs_dfs/
│   ├── lab13_randomized_quicksort/
│   ├── lab14_string_matching/
│   └── lab15_real_time_problem/
└── tests/
    └── run_tests.sh
```

## Compiling a Single Lab

```bash
g++ -std=c++17 -O2 exercises/lab01_insertion_sort/insertion_sort.cpp -o insertion_sort
./insertion_sort
```

## Running All Tests

```bash
bash tests/run_tests.sh
```

The test script compiles every program, pipes sample inputs, and checks expected output substrings.