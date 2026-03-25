// Lab 15 – Discussion over Analysing a Real-Time Problem
// Problem: CPU Job Scheduling with Deadlines (Greedy)
// Description: Given n jobs, each with a deadline and profit, schedule them
//              to maximise total profit. Each job takes 1 unit of time and
//              must finish by its deadline. Uses a greedy + Union-Find approach.
//              Time complexity: O(n log n) with sorting.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    string id;
    int deadline;
    int profit;
};

// Union-Find for free time slot management
struct SlotUF {
    vector<int> parent;
    SlotUF(int n) : parent(n + 1) {
        for (int i = 0; i <= n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    // Mark slot x as used; route future queries to x-1
    void useSlot(int x) { parent[x] = x - 1; }
};

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);
    int maxDeadline = 0;
    cout << "Enter job id, deadline, and profit for each job:\n";
    for (auto& j : jobs) {
        cin >> j.id >> j.deadline >> j.profit;
        maxDeadline = max(maxDeadline, j.deadline);
    }

    // Sort jobs by profit descending (greedy choice)
    sort(jobs.begin(), jobs.end(),
         [](const Job& a, const Job& b) { return a.profit > b.profit; });

    SlotUF uf(maxDeadline);
    vector<pair<int, string>> schedule(maxDeadline + 1, {0, ""});
    int totalProfit = 0;
    int jobsScheduled = 0;

    for (const auto& job : jobs) {
        int slot = uf.find(job.deadline); // latest free slot <= deadline
        if (slot == 0) continue;          // no free slot available
        schedule[slot] = {job.profit, job.id};
        totalProfit += job.profit;
        jobsScheduled++;
        uf.useSlot(slot);
    }

    cout << "\nScheduled Jobs (time slot -> job):\n";
    for (int t = 1; t <= maxDeadline; t++) {
        if (!schedule[t].second.empty())
            cout << "  Slot " << t << ": Job " << schedule[t].second
                 << "  (profit=" << schedule[t].first << ")\n";
    }
    cout << "Total jobs scheduled: " << jobsScheduled << "\n";
    cout << "Total profit: " << totalProfit << "\n";
    return 0;
}
