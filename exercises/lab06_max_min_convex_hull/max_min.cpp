// Lab 06 – Finding Maximum and Minimum in an Array
// Description: Find both max and min using divide-and-conquer.
//              Comparisons: ~3n/2 - 2 (vs 2n-2 for naive approach).

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct MinMax { int mn, mx; };

MinMax findMinMax(const vector<int>& arr, int low, int high) {
    if (low == high) return {arr[low], arr[low]};
    if (high - low == 1) {
        return {min(arr[low], arr[high]), max(arr[low], arr[high])};
    }
    int mid = low + (high - low) / 2;
    MinMax left  = findMinMax(arr, low, mid);
    MinMax right = findMinMax(arr, mid + 1, high);
    return {min(left.mn, right.mn), max(left.mx, right.mx)};
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int& x : arr) cin >> x;

    MinMax result = findMinMax(arr, 0, n - 1);
    cout << "Minimum: " << result.mn << "\n";
    cout << "Maximum: " << result.mx << "\n";
    return 0;
}
