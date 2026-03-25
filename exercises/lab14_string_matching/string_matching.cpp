// Lab 14 – String Matching Algorithms
// Description: Implement three string matching algorithms and compare them:
//   1. Naive (Brute-Force)  – O(nm)
//   2. KMP (Knuth-Morris-Pratt) – O(n + m)
//   3. Rabin-Karp (rolling hash) – O(n + m) average

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ---- Naive String Matching ----
vector<int> naiveSearch(const string& text, const string& pattern) {
    vector<int> matches;
    int n = text.size(), m = pattern.size();
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) j++;
        if (j == m) matches.push_back(i);
    }
    return matches;
}

// ---- KMP ----
vector<int> buildLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0, i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) { lps[i++] = ++len; }
        else if (len) { len = lps[len - 1]; }
        else { lps[i++] = 0; }
    }
    return lps;
}

vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> matches;
    int n = text.size(), m = pattern.size();
    vector<int> lps = buildLPS(pattern);
    int i = 0, j = 0;
    while (i < n) {
        if (text[i] == pattern[j]) { i++; j++; }
        if (j == m) { matches.push_back(i - j); j = lps[j - 1]; }
        else if (i < n && text[i] != pattern[j]) {
            if (j) j = lps[j - 1];
            else   i++;
        }
    }
    return matches;
}

// ---- Rabin-Karp ----
vector<int> rabinKarpSearch(const string& text, const string& pattern) {
    vector<int> matches;
    int n = text.size(), m = pattern.size();
    const long long BASE = 256, MOD = 101;
    long long hPat = 0, hTxt = 0, h = 1;

    for (int i = 0; i < m - 1; i++) h = (h * BASE) % MOD;
    for (int i = 0; i < m; i++) {
        hPat = (BASE * hPat + pattern[i]) % MOD;
        hTxt = (BASE * hTxt + text[i])    % MOD;
    }
    for (int i = 0; i <= n - m; i++) {
        if (hPat == hTxt) {
            if (text.substr(i, m) == pattern) matches.push_back(i);
        }
        if (i < n - m) {
            hTxt = (BASE * (hTxt - text[i] * h) + text[i + m]) % MOD;
            if (hTxt < 0) hTxt += MOD;
        }
    }
    return matches;
}

void printMatches(const string& algo, const vector<int>& matches) {
    cout << algo << ": ";
    if (matches.empty()) { cout << "no match found\n"; return; }
    for (int idx : matches) cout << idx << " ";
    cout << "\n";
}

int main() {
    string text, pattern;
    cout << "Enter text:    ";
    cin >> text;
    cout << "Enter pattern: ";
    cin >> pattern;

    if ((int)pattern.size() > (int)text.size()) {
        cout << "Pattern longer than text.\n";
        return 0;
    }

    printMatches("Naive     matches at index(es)", naiveSearch(text, pattern));
    printMatches("KMP       matches at index(es)", kmpSearch(text, pattern));
    printMatches("Rabin-Karp matches at index(es)", rabinKarpSearch(text, pattern));
    return 0;
}
