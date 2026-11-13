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

class Stack {
    struct Node {
        int val;
        Node* next;

        Node(int x, Node* p) : val(x), next(p) {}
    };

    Node* head = nullptr;
    int cnt = 0;

public:
    Stack() = default;
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    ~Stack() {
        clear();
    }

    bool empty() const {
        return cnt == 0;
    }

    int size() const {
        return cnt;
    }

    void push(int x) {
        head = new Node(x, head);
        ++cnt;
    }

    void pop() {
        if (empty()) return;

        Node* p = head;
        head = head->next;
        delete p;
        --cnt;
    }

    int top() const {
        if (empty()) throw out_of_range("Стек пуст");
        return head->val;
    }

    void clear() {
        while (!empty()) pop();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Stack s;
    s.push(4);
    s.push(8);
    s.push(12);

    cout << s.top() << '\n';
    s.pop();
    cout << s.top() << '\n';
    cout << s.size() << '\n';
}