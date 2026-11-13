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

class BST {
    struct Node {
        int val;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(int x) : val(x) {}
    };

    Node* root = nullptr;
    int cnt = 0;

    Node* insert(Node* p, int x) {
        if (!p) {
            ++cnt;
            return new Node(x);
        }

        if (x < p->val) p->left = insert(p->left, x);
        if (x > p->val) p->right = insert(p->right, x);
        return p;
    }

    Node* erase(Node* p, int x) {
        if (!p) return nullptr;

        if (x < p->val) {
            p->left = erase(p->left, x);
        } else if (x > p->val) {
            p->right = erase(p->right, x);
        } else {
            if (!p->left || !p->right) {
                Node* q = p->left ? p->left : p->right;
                delete p;
                --cnt;
                return q;
            }

            Node* q = p->right;
            while (q->left) q = q->left;
            p->val = q->val;
            p->right = erase(p->right, q->val);
        }
        return p;
    }

    void print(Node* p) const {
        if (!p) return;
        print(p->left);
        cout << p->val << ' ';
        print(p->right);
    }

    void clear(Node* p) {
        if (!p) return;
        clear(p->left);
        clear(p->right);
        delete p;
    }

public:
    BST() = default;
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    ~BST() {
        clear();
    }

    bool empty() const {
        return cnt == 0;
    }

    int size() const {
        return cnt;
    }

    void insert(int x) {
        root = insert(root, x);
    }

    void erase(int x) {
        root = erase(root, x);
    }

    bool find(int x) const {
        Node* p = root;
        while (p) {
            if (x == p->val) return true;
            p = x < p->val ? p->left : p->right;
        }
        return false;
    }

    int min() const {
        if (empty()) throw out_of_range("Дерево пусто");
        Node* p = root;
        while (p->left) p = p->left;
        return p->val;
    }

    int max() const {
        if (empty()) throw out_of_range("Дерево пусто");
        Node* p = root;
        while (p->right) p = p->right;
        return p->val;
    }

    void clear() {
        clear(root);
        root = nullptr;
        cnt = 0;
    }

    void print() const {
        print(root);
        cout << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    BST tree;
    for (int x : {7, 3, 10, 1, 5, 8, 12}) tree.insert(x);
    tree.print();

    cout << tree.find(5) << '\n';
    tree.erase(7);
    tree.print();
}