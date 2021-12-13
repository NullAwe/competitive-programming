#include <bits/stdc++.h>
using namespace std;

struct DSU {

  vector<int> e;
  multiset<int> s;

  DSU(int N) {
    e = vector<int>(N, -1);
    for (int i = 0; i < N; ++i) s.insert(1);
  }

  int get(int x) {
    return e[x] < 0 ? x : e[x] = get(e[x]);
  }

  bool sameSet(int a, int b) {
    return get(a) == get(b);
  }

  int size(int x) {
    return -e[get(x)];
  }

  bool unite(int x, int y) {
    x = get(x), y = get(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    s.erase(s.find(size(x)));
    s.erase(s.find(size(y)));
    e[x] += e[y]; e[y] = x;
    s.insert(size(x));
    return true;
  }
};

void solve() {
  int n, d; cin >> n >> d;
  DSU dsu(n);
  int extra = 0;
  for (int i = 0; i < d; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    if (dsu.sameSet(a, b)) ++extra;
    dsu.unite(a, b);
    auto it = dsu.s.end();
    --it;
    int sum = 0;
    for (int i = 0; i <= extra; --it, ++i) sum += *it;
    // Output:
    cout << sum - 1 << endl;
  }
}

int main() {
  solve();
  return 0;
}
