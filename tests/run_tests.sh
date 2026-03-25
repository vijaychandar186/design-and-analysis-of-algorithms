#!/usr/bin/env bash
# run_tests.sh – Compile and smoke-test all DAA lab programs.
# Usage: bash tests/run_tests.sh
# Requirements: g++ (C++17 or later)

set -euo pipefail
CXX=${CXX:-g++}
CXXFLAGS="-std=c++17 -O2 -Wall"
ROOT="$(cd "$(dirname "$0")/.." && pwd)/exercises"
PASS=0; FAIL=0; SKIP=0

run() {
    local label="$1" src="$2" input="$3" expected="$4"
    local bin; bin=$(mktemp /tmp/daa_XXXXXX)
    if ! $CXX $CXXFLAGS "$src" -o "$bin" 2>/dev/null; then
        echo "[FAIL] $label  (compile error)"; FAIL=$((FAIL+1)); return
    fi
    local out; out=$(echo "$input" | timeout 5 "$bin" 2>/dev/null || true)
    rm -f "$bin"
    if echo "$out" | grep -qF "$expected"; then
        echo "[PASS] $label"; PASS=$((PASS+1))
    else
        echo "[FAIL] $label"
        echo "       expected to contain: $expected"
        echo "       got: $out"
        FAIL=$((FAIL+1))
    fi
}

echo "=== Design and Analysis of Algorithms – Test Suite ==="
echo ""

# Lab 01 – Insertion Sort
run "Lab01 insertion_sort" \
    "$ROOT/lab01_insertion_sort/insertion_sort.cpp" \
    "5
5 3 1 4 2" \
    "1 2 3 4 5"

# Lab 02 – Bubble Sort
run "Lab02 bubble_sort" \
    "$ROOT/lab02_bubble_sort/bubble_sort.cpp" \
    "4
4 2 3 1" \
    "1 2 3 4"

# Lab 03 – Merge Sort
run "Lab03 merge_sort" \
    "$ROOT/lab03_merge_sort_linear_search/merge_sort.cpp" \
    "6
6 5 4 3 2 1" \
    "1 2 3 4 5 6"

# Lab 03 – Linear Search (found)
run "Lab03 linear_search (found)" \
    "$ROOT/lab03_merge_sort_linear_search/linear_search.cpp" \
    "5
10 20 30 40 50
30" \
    "index 2"

# Lab 03 – Linear Search (not found)
run "Lab03 linear_search (not found)" \
    "$ROOT/lab03_merge_sort_linear_search/linear_search.cpp" \
    "3
1 2 3
9" \
    "not found"

# Lab 04 – Quicksort
run "Lab04 quicksort" \
    "$ROOT/lab04_quicksort_binary_search/quicksort.cpp" \
    "5
3 1 4 1 5" \
    "1 1 3 4 5"

# Lab 04 – Binary Search (found)
run "Lab04 binary_search (found)" \
    "$ROOT/lab04_quicksort_binary_search/binary_search.cpp" \
    "5
1 3 5 7 9
7" \
    "index 3"

# Lab 04 – Binary Search (not found)
run "Lab04 binary_search (not found)" \
    "$ROOT/lab04_quicksort_binary_search/binary_search.cpp" \
    "4
2 4 6 8
5" \
    "not found"

# Lab 05 – Strassen (2x2)
run "Lab05 strassen 2x2" \
    "$ROOT/lab05_strassen_matrix/strassen.cpp" \
    "2
1 2
3 4
5 6
7 8" \
    "19"

# Lab 06 – Max/Min
run "Lab06 max_min" \
    "$ROOT/lab06_max_min_convex_hull/max_min.cpp" \
    "6
3 1 4 1 5 9" \
    "Minimum: 1"

# Lab 06 – Convex Hull
run "Lab06 convex_hull" \
    "$ROOT/lab06_max_min_convex_hull/convex_hull.cpp" \
    "6
0 0
1 1
2 0
0 2
2 2
1 3" \
    "Convex Hull"

# Lab 07 – Huffman
run "Lab07 huffman" \
    "$ROOT/lab07_huffman_knapsack/huffman.cpp" \
    "4
a 5
b 9
c 12
d 13" \
    "Huffman Codes"

# Lab 07 – Knapsack Greedy
run "Lab07 knapsack_greedy" \
    "$ROOT/lab07_huffman_knapsack/knapsack_greedy.cpp" \
    "3
50
60 10
100 20
120 30" \
    "Maximum value"

# Lab 08 – Tree Traversals
run "Lab08 tree_traversals" \
    "$ROOT/lab08_tree_traversals_kruskal/tree_traversals.cpp" \
    "5
5 3 7 1 4" \
    "In-order"

# Lab 08 – Kruskal
run "Lab08 kruskal" \
    "$ROOT/lab08_tree_traversals_kruskal/kruskal.cpp" \
    "4 5
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4" \
    "Total MST weight: 19"

# Lab 09 – LCS (length 4 is the correct answer; multiple valid subsequences exist)
run "Lab09 lcs" \
    "$ROOT/lab09_lcs/lcs.cpp" \
    "ABCBDAB
BDCABA" \
    "LCS length: 4"

# Lab 10 – N-Queens
run "Lab10 n_queens N=4" \
    "$ROOT/lab10_n_queens/n_queens.cpp" \
    "4" \
    "Total solutions for N=4: 2"

# Lab 11 – TSP
run "Lab11 tsp" \
    "$ROOT/lab11_tsp/tsp.cpp" \
    "4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0" \
    "Optimal tour cost: 80"

# Lab 12 – BFS/DFS
run "Lab12 bfs_dfs" \
    "$ROOT/lab12_bfs_dfs/bfs_dfs.cpp" \
    "5 5
0 1
0 2
1 3
2 4
3 4
0" \
    "BFS from vertex 0"

# Lab 13 – Randomized Quicksort
run "Lab13 randomized_quicksort" \
    "$ROOT/lab13_randomized_quicksort/randomized_quicksort.cpp" \
    "5
9 3 7 1 5" \
    "1 3 5 7 9"

# Lab 14 – String Matching
run "Lab14 string_matching (found)" \
    "$ROOT/lab14_string_matching/string_matching.cpp" \
    "AABAACAADAABAABA
AABA" \
    "0"

run "Lab14 string_matching (not found)" \
    "$ROOT/lab14_string_matching/string_matching.cpp" \
    "hello
xyz" \
    "no match"

# Lab 15 – Job Scheduling
run "Lab15 job_scheduling" \
    "$ROOT/lab15_real_time_problem/job_scheduling.cpp" \
    "4
J1 2 100
J2 1 19
J3 2 27
J4 1 25" \
    "Total profit"

echo ""
echo "=== Results: $PASS passed, $FAIL failed, $SKIP skipped ==="
