#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

inline int query(int v) {
  cout << "? " << v + 1 << endl;
  int ans; cin >> ans;
  return ans - 1;
}

inline void answer(vector<int>& colors) {
  cout << '!';
  for (int num : colors) cout << ' ' << num + 1;
  cout << endl;
}

struct DSU {

  vector<int> r, p;

  DSU(int n) : r(n), p(n) {
    for (int i = 0; i < n; ++i) p[i] = i;
  }

  int find(int a) {
    return a == p[a] ? a : p[a] = find(p[a]);
  }

  void link(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (r[a] < r[b]) swap(a, b);
    if (r[a] == r[b]) ++r[a];
    p[b] = a;
  }
};

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<pii> ps(n); for (int i = 0; i < n; ++i) ps[i] = {arr[i], i};
  sort(ps.begin(), ps.end()), reverse(ps.begin(), ps.end());
  vector<bool> vis(n);
  DSU dsu(n);
  for (int i = 0; i < n; ++i) {
    int v = ps[i].second, num = ps[i].first;
    if (vis[v]) continue;
    vis[v] = true;
    for (int j = 0; j < num; ++j) {
      int u = query(v);
      dsu.link(v, u);
      if (vis[u]) break;
      vis[u] = true;
    }
  }
  vector<int> colors(n);
  for (int i = 0; i < n; ++i) colors[i] = dsu.find(i);
  answer(colors);
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
