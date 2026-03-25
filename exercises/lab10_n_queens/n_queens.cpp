// Lab 10 – N-Queens Problem (Backtracking)
// Description: Place N queens on an NxN chessboard so that no two queens
//              attack each other. Prints all solutions using backtracking.
//              Time complexity: O(N!) in the worst case.

#include <iostream>
#include <vector>
using namespace std;

int N;
int solutionCount = 0;

bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col) return false;                    // same column
        if (abs(board[i] - col) == abs(i - row)) return false; // diagonal
    }
    return true;
}

void printBoard(const vector<int>& board) {
    cout << "Solution " << ++solutionCount << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << (board[i] == j ? "Q " : ". ");
        cout << "\n";
    }
    cout << "\n";
}

void solve(vector<int>& board, int row) {
    if (row == N) { printBoard(board); return; }
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solve(board, row + 1);
        }
    }
}

int main() {
    cout << "Enter value of N: ";
    cin >> N;

    vector<int> board(N, -1);
    solve(board, 0);

    if (solutionCount == 0)
        cout << "No solution exists for N=" << N << "\n";
    else
        cout << "Total solutions for N=" << N << ": " << solutionCount << "\n";
    return 0;
}
