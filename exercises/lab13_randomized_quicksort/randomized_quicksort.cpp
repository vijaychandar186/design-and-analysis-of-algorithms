// Lab 13 – Randomized Quicksort
// Description: Sort an array using quicksort with a randomly chosen pivot.
//              Random pivot selection gives expected O(n log n) time and
//              avoids the O(n^2) worst case of deterministic pivot selection.

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int randomPartition(vector<int>& arr, int low, int high) {
    // Swap a random element into the last position as pivot
    int randIdx = low + rand() % (high - low + 1);
    swap(arr[randIdx], arr[high]);

    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

void printArray(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int& x : arr) cin >> x;

    cout << "Before sorting: ";
    printArray(arr);
    randomizedQuickSort(arr, 0, n - 1);
    cout << "After sorting:  ";
    printArray(arr);
    return 0;
}
