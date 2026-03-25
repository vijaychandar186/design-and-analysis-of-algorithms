// Lab 06 – Convex Hull Problem
// Description: Find the convex hull of a set of 2D points using
//              Graham Scan algorithm. Time complexity: O(n log n).

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

struct Point { int x, y; };

// Cross product of vectors OA and OB
long long crossProduct(const Point& O, const Point& A, const Point& B) {
    return (long long)(A.x - O.x) * (B.y - O.y)
         - (long long)(A.y - O.y) * (B.x - O.x);
}

long long dist2(const Point& a, const Point& b) {
    return (long long)(a.x - b.x) * (a.x - b.x)
         + (long long)(a.y - b.y) * (a.y - b.y);
}

vector<Point> convexHull(vector<Point> pts) {
    int n = pts.size();
    if (n < 3) return pts;

    // Find bottom-most (then left-most) point
    int pivot = 0;
    for (int i = 1; i < n; i++)
        if (pts[i].y < pts[pivot].y ||
           (pts[i].y == pts[pivot].y && pts[i].x < pts[pivot].x))
            pivot = i;
    swap(pts[0], pts[pivot]);
    Point p0 = pts[0];

    // Sort by polar angle with p0
    sort(pts.begin() + 1, pts.end(), [&](const Point& a, const Point& b) {
        long long cp = crossProduct(p0, a, b);
        if (cp != 0) return cp > 0;
        return dist2(p0, a) < dist2(p0, b);
    });

    // Graham scan
    stack<Point> hull;
    hull.push(pts[0]);
    hull.push(pts[1]);
    hull.push(pts[2]);

    for (int i = 3; i < n; i++) {
        while (hull.size() > 1) {
            Point top = hull.top(); hull.pop();
            if (crossProduct(hull.top(), top, pts[i]) > 0) {
                hull.push(top);
                break;
            }
        }
        hull.push(pts[i]);
    }

    vector<Point> result;
    while (!hull.empty()) { result.push_back(hull.top()); hull.pop(); }
    return result;
}

int main() {
    int n;
    cout << "Enter number of points: ";
    cin >> n;
    vector<Point> pts(n);
    cout << "Enter points (x y):\n";
    for (auto& p : pts) cin >> p.x >> p.y;

    vector<Point> hull = convexHull(pts);
    cout << "Convex Hull vertices (" << hull.size() << " points):\n";
    for (const auto& p : hull)
        cout << "(" << p.x << ", " << p.y << ")\n";
    return 0;
}
