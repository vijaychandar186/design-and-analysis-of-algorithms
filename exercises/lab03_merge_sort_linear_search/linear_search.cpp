// Lab 03 – Recurrence Type: Linear Search
// Description: Search for a target element in an unsorted array.
//              Time complexity: O(n) worst case, O(1) best case.

#include <iostream>
#include <vector>
using namespace std;

int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int& x : arr) cin >> x;

    int target;
    cout << "Enter element to search: ";
    cin >> target;

    int idx = linearSearch(arr, target);
    if (idx != -1)
        cout << "Element " << target << " found at index " << idx << "\n";
    else
        cout << "Element " << target << " not found in array\n";
    return 0;
}
