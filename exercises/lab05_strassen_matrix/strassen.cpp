// Lab 05 – Strassen Matrix Multiplication
// Description: Multiply two 2x2 matrices using Strassen's algorithm (7 multiplications
//              instead of 8). Generalises recursively for 2^n x 2^n matrices.
//              Time complexity: O(n^2.807) vs O(n^3) for naive multiplication.

#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix add(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix sub(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Strassen multiplication for 2^n x 2^n matrices
Matrix strassen(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int half = n / 2;

    // Split into quadrants
    Matrix A11(half, vector<int>(half)), A12(half, vector<int>(half)),
           A21(half, vector<int>(half)), A22(half, vector<int>(half));
    Matrix B11(half, vector<int>(half)), B12(half, vector<int>(half)),
           B21(half, vector<int>(half)), B22(half, vector<int>(half));

    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];           A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];    A22[i][j] = A[i + half][j + half];
            B11[i][j] = B[i][j];           B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];    B22[i][j] = B[i + half][j + half];
        }

    // 7 Strassen products
    Matrix M1 = strassen(add(A11, A22), add(B11, B22));
    Matrix M2 = strassen(add(A21, A22), B11);
    Matrix M3 = strassen(A11, sub(B12, B22));
    Matrix M4 = strassen(A22, sub(B21, B11));
    Matrix M5 = strassen(add(A11, A12), B22);
    Matrix M6 = strassen(sub(A21, A11), add(B11, B12));
    Matrix M7 = strassen(sub(A12, A22), add(B21, B22));

    // Combine quadrants
    Matrix C11 = add(sub(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(sub(add(M1, M3), M2), M6);

    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++) {
            C[i][j]               = C11[i][j];
            C[i][j + half]        = C12[i][j];
            C[i + half][j]        = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    return C;
}

void printMatrix(const Matrix& M) {
    for (const auto& row : M) {
        for (int x : row) cout << x << "\t";
        cout << "\n";
    }
}

int main() {
    int n;
    cout << "Enter matrix size (must be power of 2, e.g. 2 or 4): ";
    cin >> n;

    Matrix A(n, vector<int>(n)), B(n, vector<int>(n));
    cout << "Enter elements of matrix A (" << n << "x" << n << "):\n";
    for (auto& row : A) for (int& x : row) cin >> x;

    cout << "Enter elements of matrix B (" << n << "x" << n << "):\n";
    for (auto& row : B) for (int& x : row) cin >> x;

    Matrix C = strassen(A, B);
    cout << "Result of A x B (Strassen):\n";
    printMatrix(C);
    return 0;
}
