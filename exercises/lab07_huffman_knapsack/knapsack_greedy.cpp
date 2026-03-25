// Lab 07 – Fractional Knapsack (Greedy)
// Description: Maximise the total value of items placed in a knapsack of
//              capacity W using a greedy value/weight ratio strategy.
//              Works optimally for the fractional variant. O(n log n).

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value, weight;
    double ratio() const { return (double)value / weight; }
};

double fractionalKnapsack(vector<Item>& items, int capacity) {
    sort(items.begin(), items.end(),
         [](const Item& a, const Item& b) { return a.ratio() > b.ratio(); });

    double totalValue = 0.0;
    int remaining = capacity;

    for (const auto& item : items) {
        if (remaining <= 0) break;
        if (item.weight <= remaining) {
            totalValue += item.value;
            remaining  -= item.weight;
            cout << "  Took whole item (v=" << item.value
                 << ", w=" << item.weight << ")\n";
        } else {
            double fraction = (double)remaining / item.weight;
            totalValue += item.value * fraction;
            cout << "  Took " << fraction * 100 << "% of item (v="
                 << item.value << ", w=" << item.weight << ")\n";
            remaining = 0;
        }
    }
    return totalValue;
}

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    vector<Item> items(n);
    cout << "Enter value and weight for each item:\n";
    for (auto& item : items) cin >> item.value >> item.weight;

    cout << "\nSelection:\n";
    double maxValue = fractionalKnapsack(items, capacity);
    cout << "Maximum value in knapsack: " << maxValue << "\n";
    return 0;
}
