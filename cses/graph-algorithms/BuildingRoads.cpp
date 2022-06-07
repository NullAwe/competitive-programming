#include <bits/stdc++.h>
using namespace std;

vector<int> r, p;

int find(int v) {
  return v == p[v] ? v : p[v] = find(p[v]);
}

void link(int v, int u) {
  v = find(v), u = find(u);
  if (v == u) return;
  if (r[v] < r[u]) swap(v, u);
  if (r[v] == r[u]) ++r[v];
  p[u] = v;
}

int main() {
  int n, m; cin >> n >> m;
  r = vector<int>(n), p = vector<int>(n);
  for (int i = 0; i < n; ++i) p[i] = i;
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    link(a, b);
  }
  set<int> ps; for (int i = 0; i < n; ++i) ps.insert(find(i));
  cout << ps.size() - 1 << '\n';
  int from = *ps.begin(); ps.erase(ps.begin());
  for (int to : ps) cout << from + 1 << ' ' << to + 1 << '\n';
  return 0;
}
