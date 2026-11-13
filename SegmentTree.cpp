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

class SegmentTree {
    struct Node {
        int l;
        int r;
        ll sum = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(int a, int b) : l(a), r(b) {}
    };

    Node* root = nullptr;
    int n = 0;

    Node* build(const vector<int>& a, int l, int r) {
        Node* p = new Node(l, r);
        if (l == r) {
            p->sum = a[l];
            return p;
        }

        int m = (l + r) / 2;
        p->left = build(a, l, m);
        p->right = build(a, m + 1, r);
        p->sum = p->left->sum + p->right->sum;
        return p;
    }

    void update(Node* p, int i, int x) {
        if (p->l == p->r) {
            p->sum = x;
            return;
        }

        if (i <= p->left->r) update(p->left, i, x);
        else update(p->right, i, x);
        p->sum = p->left->sum + p->right->sum;
    }

    ll query(Node* p, int l, int r) const {
        if (!p || r < p->l || p->r < l) return 0;
        if (l <= p->l && p->r <= r) return p->sum;
        return query(p->left, l, r) + query(p->right, l, r);
    }

    void clear(Node* p) {
        if (!p) return;
        clear(p->left);
        clear(p->right);
        delete p;
    }

public:
    // Сумма на отрезке, индексы с нуля.
    explicit SegmentTree(const vector<int>& a) {
        n = (int)a.size();
        if (n > 0) root = build(a, 0, n - 1);
    }

    SegmentTree(const SegmentTree&) = delete;
    SegmentTree& operator=(const SegmentTree&) = delete;

    ~SegmentTree() {
        clear(root);
    }

    int size() const {
        return n;
    }

    void update(int i, int x) {
        if (i < 0 || i >= n) throw out_of_range("Неверный индекс");
        update(root, i, x);
    }

    ll query(int l, int r) const {
        if (l < 0 || r >= n || l > r) {
            throw out_of_range("Неверный отрезок");
        }
        return query(root, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> a = {2, 4, 1, 7, 3};
    SegmentTree tree(a);

    cout << tree.query(1, 3) << '\n';
    tree.update(2, 10);
    cout << tree.query(1, 3) << '\n';
}