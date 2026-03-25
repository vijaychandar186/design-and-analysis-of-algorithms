// Lab 04 – Binary Search
// Description: Search a sorted array for a target using binary search.
//              Time complexity: O(log n), Space: O(1) iterative.

#include <iostream>
#include <vector>
using namespace std;

int binarySearch(const vector<int>& arr, int target) {
    int low = 0, high = (int)arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    int n;
    cout << "Enter number of elements (sorted): ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter sorted elements: ";
    for (int& x : arr) cin >> x;

    int target;
    cout << "Enter element to search: ";
    cin >> target;

    int idx = binarySearch(arr, target);
    if (idx != -1)
        cout << "Element " << target << " found at index " << idx << "\n";
    else
        cout << "Element " << target << " not found in array\n";
    return 0;
}
