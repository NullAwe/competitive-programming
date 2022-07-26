#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> r, p;

int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

void link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return;
  if (r[a] < r[b]) swap(a, b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
}

void solve() {
  int n; cin >> n;
  r = vector<int>(n), p = vector<int>(n); for (int i = 0; i < n; ++i) p[i] = i;
  vector<string> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<pii> edges;
  vector<int> ml(n), mr(n); for (int i = 0; i < n; ++i) ml[i] = mr[i] = i;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n - i; ++j) {
      if (arr[j][i] == '0') continue;
      int l = j, r = i + j;
      if (find(l) == find(r)) {
        ml[r] = min(ml[r], l), mr[l] = max(mr[l], r);
        continue;
      }
      pii rng = {mr[l] + 1, ml[r] - 1};
      if (rng.first < rng.second) {
        edges.push_back({l, rng.second}), edges.push_back({r, rng.first});
        link(l, rng.second), link(r, rng.first);
        for (int v = rng.first + 1; v < rng.second; ++v)
          if (find(l) != find(v) && find(r) != find(v)) edges.push_back({l, v}), link(l, v);
      }
      edges.push_back({l, r});
      link(l, r);
      ml[r] = min(ml[r], l), mr[l] = max(mr[l], r);
    }
  }
  for (pii edge : edges) cout << edge.first + 1 << ' ' << edge.second + 1 << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
