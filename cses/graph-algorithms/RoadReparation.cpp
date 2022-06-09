#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<int> p, r;

int find(int v) { return p[v] == v ? v : p[v] = find(p[v]); }

bool link(int v, int u) {
  v = find(v), u = find(u);
  if (v == u) return false;
  if (r[v] == r[u]) ++r[v];
  if (r[v] < r[u]) swap(v, u);
  p[u] = v;
  return true;
}

int main() {
  int n, m; cin >> n >> m;
  p = vector<int>(n), r = vector<int>(n);
  for (int i = 0; i < n; ++i) p[i] = i;
  vector<pair<int, pii>> roads(m);
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w; --a, --b;
    roads[i] = {w, {a, b}};
  }
  sort(roads.begin(), roads.end());
  ll ans = 0;
  for (pair<int, pii> road : roads) if (link(road.second.first, road.second.second)) ans += road.first;
  for (int i = 1; i < n; ++i) {
    if (link(i - 1, i)) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
  }
  cout << ans << '\n';
  return 0;
}
