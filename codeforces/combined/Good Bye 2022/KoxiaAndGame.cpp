#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const int MOD = 998244353;

struct DSU {
  vector<int> r, p;

  DSU(int n) : r(n), p(n) {
    for (int i = 0; i < n; ++i) p[i] = i;
  }

  int find(int a) { return a == p[a] ? a : p[a] = find(p[a]);}

  void link(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (r[a] < r[b]) swap(a, b);
    if (r[a] == r[b]) ++r[a];
    p[b] = a;
  }
};

inline void solve() {
  int n; cin >> n;
  vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
  vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
  set<int> need; for (int i = 1; i <= n; ++i) need.insert(i);
  vector<pii> edges;
  DSU dsu(n + 1);
  ll ways = 1;
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i]) {
      edges.push_back({a[i], b[i]});
      continue;
    }
    if (!need.count(a[i])) {
      cout << 0 << '\n';
      return;
    }
    need.erase(a[i]);
    ways = ways * n % MOD;
  }
  vector<vector<int>> eg(n + 1);
  queue<int> q;
  for (pii p : edges) {
    if (!need.count(p.first) && !need.count(p.second)) {
      cout << 0 << '\n';
      return;
    }
    if (!need.count(p.first)) {
      q.push(p.second);
    } else if (!need.count(p.second)) {
      q.push(p.first);
    } else {
      eg[p.first].push_back(p.second);
      eg[p.second].push_back(p.first);
    }
  }
  while (q.size()) {
    int top = q.front(); q.pop();
    if (!need.count(top)) {
      cout << 0 << '\n';
      return;
    }
    need.erase(top);
    for (int num : eg[top]) if (need.count(num)) q.push(num);
    eg[top].clear();
  }
  for (pii p : edges) {
    if (need.count(p.first) && need.count(p.second)) {
      dsu.link(p.first, p.second);
    }
  }
  vector<int> eds(n + 1);
  for (pii p : edges) {
    if (need.count(p.first) && need.count(p.second)) {
      ++eds[dsu.find(p.first)];
    }
  }
  vector<int> sz(n + 1);
  for (int i = 1; i <= n; ++i) ++sz[dsu.find(i)];
  for (int i = 1; i <= n; ++i) {
    if (i != dsu.find(i) || !need.count(i)) continue;
    if (sz[i] != eds[i]) {
      cout << 0 << '\n';
      return;
    }
    ways = 2 * ways % MOD;
  }
  cout << ways << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
