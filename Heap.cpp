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

class Heap {
    vector<int> a;

    void up(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (a[p] >= a[i]) break;
            swap(a[p], a[i]);
            i = p;
        }
    }

    void down(int i) {
        int n = (int)a.size();
        while (true) {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int j = i;

            if (l < n && a[l] > a[j]) j = l;
            if (r < n && a[r] > a[j]) j = r;
            if (j == i) break;

            swap(a[i], a[j]);
            i = j;
        }
    }

public:
    // Максимальная куча.
    bool empty() const {
        return a.empty();
    }

    int size() const {
        return (int)a.size();
    }

    void push(int x) {
        a.push_back(x);
        up((int)a.size() - 1);
    }

    void pop() {
        if (empty()) return;
        swap(a[0], a.back());
        a.pop_back();
        if (!empty()) down(0);
    }

    int top() const {
        if (empty()) throw out_of_range("Куча пуста");
        return a[0];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Heap heap;
    for (int x : {8, 3, 15, 6}) heap.push(x);

    while (!heap.empty()) {
        cout << heap.top() << ' ';
        heap.pop();
    }
    cout << '\n';
}