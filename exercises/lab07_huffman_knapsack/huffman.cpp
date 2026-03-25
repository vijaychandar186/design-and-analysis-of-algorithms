// Lab 07 – Huffman Coding (Greedy)
// Description: Build an optimal prefix-free binary code for a set of characters
//              with given frequencies using a greedy min-heap strategy.
//              Time complexity: O(n log n).

#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct HNode {
    char ch;
    int freq;
    HNode *left, *right;
    HNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HNode* a, HNode* b) { return a->freq > b->freq; }
};

void generateCodes(HNode* root, const string& code,
                   unordered_map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch] = code.empty() ? "0" : code;
        return;
    }
    generateCodes(root->left,  code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

HNode* buildHuffmanTree(const unordered_map<char, int>& freq) {
    priority_queue<HNode*, vector<HNode*>, Compare> pq;
    for (const auto& [ch, f] : freq)
        pq.push(new HNode(ch, f));

    while (pq.size() > 1) {
        HNode* left  = pq.top(); pq.pop();
        HNode* right = pq.top(); pq.pop();
        HNode* parent = new HNode('\0', left->freq + right->freq);
        parent->left  = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.top();
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;
    unordered_map<char, int> freq;
    cout << "Enter character and frequency pairs (e.g. a 5):\n";
    for (int i = 0; i < n; i++) {
        char ch; int f;
        cin >> ch >> f;
        freq[ch] = f;
    }

    HNode* root = buildHuffmanTree(freq);
    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "\nHuffman Codes:\n";
    int totalBits = 0;
    for (const auto& [ch, code] : codes) {
        cout << "  '" << ch << "' (freq=" << freq[ch] << ") : " << code << "\n";
        totalBits += freq[ch] * code.size();
    }
    cout << "Total bits required: " << totalBits << "\n";
    return 0;
}
