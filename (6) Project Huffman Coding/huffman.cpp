// Course: CSC 6200 Advanced Algorithms
// Project: (6) Huffman Coding
// Student: Sravya Reddy Soodini
// File: huffman.cpp
//
// Build:  g++ -std=gnu++17 -O2 -Wall -Wextra -o huffman huffman.cpp
// Run 1:  ./huffman
// Run 2:  (custom input)
//         Input line 1: characters with NO spaces (distinct), e.g. abcdef
//         Input line 2: same count of integer frequencies, space-separated
//         Example:
//           abcdef
//           5 9 12 13 16 45
//
// Output:
//   Line 1: space-separated codes in PREORDER of the Huffman tree (leaves only)
//   Then:   a legend mapping char -> code (for verification)

#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long freq;
    bool isLeaf;
    char ch;                 // valid only if isLeaf = true
    Node* left = nullptr;
    Node* right = nullptr;
    char minChar;            // smallest character in this subtree (for deterministic ties)
    Node(long long f, char c) : freq(f), isLeaf(true), ch(c), minChar(c) {}
    Node(Node* L, Node* R) : freq(L->freq + R->freq), isLeaf(false), ch('\0'), left(L), right(R) {
        minChar = min(L->minChar, R->minChar);
    }
};

// Priority queue comparator for deterministic tree:
// 1) smaller freq first
// 2) if tie, smaller minChar first (lexicographic)
struct Cmp {
    bool operator()(const Node* a, const Node* b) const {
        if (a->freq != b->freq) return a->freq > b->freq;
        return a->minChar > b->minChar;
    }
};

// Build Huffman tree; returns pointer to root.
// Assumes all characters are distinct and freq.size() == S.size().
static Node* buildHuffman(const string& S, const vector<long long>& freq) {
    priority_queue<Node*, vector<Node*>, Cmp> pq;
    for (size_t i = 0; i < S.size(); ++i) {
        pq.push(new Node(freq[i], S[i]));
    }
    // Combine until single root
    while (pq.size() > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();

        // Deterministic left/right choice:
        // Make 'left' be the one that is "smaller" under Cmp's ascending order.
        Node* left = a;
        Node* right = b;
        // If 'b' should come before 'a' in ascending order, swap.
        if ( (b->freq < a->freq) || (b->freq == a->freq && b->minChar < a->minChar) ) {
            left = b; right = a;
        }
        pq.push(new Node(left, right));
    }
    return pq.top();
}

// Preorder traversal that collects codes at leaves.
// codePath accumulates '0' on left and '1' on right.
static void preorderCollect(Node* cur, string& codePath,
                            vector<string>& codesInPreorder,
                            vector<pair<char,string>>& legend) {
    if (!cur) return;
    if (cur->isLeaf) {
        // For a single-character input, ensure code is not empty
        string code = codePath.empty() ? string("0") : codePath;
        codesInPreorder.push_back(code);
        legend.push_back({cur->ch, code});
        return;
    }
    // Root, Left, Right: record only at leaves, so visit children
    if (cur->left) {
        codePath.push_back('0');
        preorderCollect(cur->left, codePath, codesInPreorder, legend);
        codePath.pop_back();
    }
    if (cur->right) {
        codePath.push_back('1');
        preorderCollect(cur->right, codePath, codesInPreorder, legend);
        codePath.pop_back();
    }
}

static void freeTree(Node* cur) {
    if (!cur) return;
    freeTree(cur->left);
    freeTree(cur->right);
    delete cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Try to read input; if not provided, use the sample.
    // Expected interactive input:
    //   Line 1: distinct characters, e.g. abcdef
    //   Line 2: frequencies, space-separated, same count
    string S;
    if (!getline(cin, S) || S.empty()) {
        S = "abcdef";
        vector<long long> f = {5, 9, 12, 13, 16, 45};
        Node* root = buildHuffman(S, f);

        vector<string> codes;
        vector<pair<char,string>> legend;
        string path;
        preorderCollect(root, path, codes, legend);

        // Print codes in preorder (leaves only), space-separated
        for (size_t i = 0; i < codes.size(); ++i) {
            if (i) cout << ' ';
            cout << codes[i];
        }
        cout << "\n";

        // Optional legend (matches sample explanation)
        for (auto& p : legend) {
            cout << p.first << " : " << p.second << "\n";
        }
        freeTree(root);
        return 0;
    }

    // Normalize input (remove spaces just in case)
    {
        string t;
        for (char c : S) if (!isspace(static_cast<unsigned char>(c))) t.push_back(c);
        S.swap(t);
    }

    vector<long long> freq;
    freq.reserve(S.size());
    {
        string line2;
        if (!getline(cin, line2)) {
            cerr << "Missing frequency line. Provide the same number of integer frequencies as characters.\n";
            return 1;
        }
        stringstream ss(line2);
        long long x;
        while (ss >> x) freq.push_back(x);
    }
    if (freq.size() != S.size()) {
        cerr << "Frequency count does not match the number of characters.\n";
        return 1;
    }

    Node* root = buildHuffman(S, freq);

    vector<string> codes;
    vector<pair<char,string>> legend;
    string path;
    preorderCollect(root, path, codes, legend);

    // Print codes in preorder (leaves only), space-separated
    for (size_t i = 0; i < codes.size(); ++i) {
        if (i) cout << ' ';
        cout << codes[i];
    }
    cout << "\n";

    // Also print the legend
    for (auto& p : legend) {
        cout << p.first << " : " << p.second << "\n";
    }

    freeTree(root);
    return 0;
}
