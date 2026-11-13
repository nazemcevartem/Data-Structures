#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>
#include <functional>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <numeric>
#include <unordered_map>
#include <stdexcept>
#define ll long long
using namespace std;

class Trie {
    struct Node {
        bool end = false;
        unordered_map<char, Node*> next;
    };

    Node* root = new Node();

    void clear(Node* p) {
        if (!p) return;
        for (auto& [c, q] : p->next) clear(q);
        delete p;
    }

public:
    Trie() = default;
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    ~Trie() {
        clear(root);
    }

    void insert(const string& s) {
        Node* p = root;
        for (char c : s) {
            if (!p->next.count(c)) p->next[c] = new Node();
            p = p->next[c];
        }
        p->end = true;
    }

    bool find(const string& s) const {
        Node* p = root;
        for (char c : s) {
            auto it = p->next.find(c);
            if (it == p->next.end()) return false;
            p = it->second;
        }
        return p->end;
    }

    bool prefix(const string& s) const {
        Node* p = root;
        for (char c : s) {
            auto it = p->next.find(c);
            if (it == p->next.end()) return false;
            p = it->second;
        }
        return true;
    }

    bool erase(const string& s) {
        Node* p = root;
        vector<pair<Node*, char>> path;

        for (char c : s) {
            auto it = p->next.find(c);
            if (it == p->next.end()) return false;
            path.push_back({p, c});
            p = it->second;
        }

        if (!p->end) return false;
        p->end = false;

        for (int i = (int)path.size() - 1; i >= 0; --i) {
            if (p->end || !p->next.empty()) break;
            Node* q = path[i].first;
            delete p;
            q->next.erase(path[i].second);
            p = q;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Trie trie;
    trie.insert("cat");
    trie.insert("car");

    cout << trie.find("cat") << '\n';
    cout << trie.prefix("ca") << '\n';
    trie.erase("cat");
    cout << trie.find("cat") << '\n';
    cout << trie.find("car") << '\n';
}