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

class List {
    struct Node {
        int val;
        Node* prev;
        Node* next;

        Node(int x) : val(x), prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int cnt = 0;

public:
    List() = default;
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    ~List() {
        clear();
    }

    bool empty() const {
        return cnt == 0;
    }

    int size() const {
        return cnt;
    }

    void push(int x) {
        Node* p = new Node(x);
        p->prev = tail;

        if (tail) tail->next = p;
        else head = p;

        tail = p;
        ++cnt;
    }

    void prepend(int x) {
        Node* p = new Node(x);
        p->next = head;

        if (head) head->prev = p;
        else tail = p;

        head = p;
        ++cnt;
    }

    void pop() {
        if (empty()) return;

        Node* p = tail;
        tail = tail->prev;

        if (tail) tail->next = nullptr;
        else head = nullptr;

        delete p;
        --cnt;
    }

    void shift() {
        if (empty()) return;

        Node* p = head;
        head = head->next;

        if (head) head->prev = nullptr;
        else tail = nullptr;

        delete p;
        --cnt;
    }

    int front() const {
        if (empty()) throw out_of_range("Список пуст");
        return head->val;
    }

    int back() const {
        if (empty()) throw out_of_range("Список пуст");
        return tail->val;
    }

    void clear() {
        while (!empty()) pop();
    }

    void print() const {
        for (Node* p = head; p; p = p->next) {
            cout << p->val << ' ';
        }
        cout << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    List a;
    a.push(10);
    a.push(20);
    a.prepend(5);
    a.print();

    a.shift();
    a.pop();
    a.print();
}