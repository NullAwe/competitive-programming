#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<int> r, p;

int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

bool link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return false;
  if (r[a] < r[b]) swap(a, b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
  return true;
}

vector<vector<int>> adj;
vector<int> sz;
vector<vector<ll>> vals;
vector<pair<pii, ll>> infos;

int dfs(int v, int p) {
  sz[v] = 1;
  for (int u : adj[v]) if (u != p) sz[v] += dfs(u, v);
  return sz[v];
}

void fill(int v, int p) {
  for (int u : adj[v]) if (u != p) fill(u, v);
  if (v == p) return;
  ll diff = vals[v][v] - vals[p][p];
  ll over = (int) sz.size() - 2 * sz[v];
  ll ans = (vals[p][p] - vals[max(v, p)][min(v, p)]) / sz[v];
  infos.push_back({{p + 1, v + 1}, ans});
}

void solve() {
  int n; cin >> n;
  vector<vector<ll>> arr(n, vector<ll>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) {
      cin >> arr[i][j];
    }
  }
  r.resize(n), p.resize(n); for (int i = 0; i < n; ++i) p[i] = i;
  set<pair<ll, pii>> ts;
  adj.resize(n);
  for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j) ts.insert({arr[i][j], {i, j}});
  while (ts.size()) {
    auto beg = *--ts.end(); ts.erase(beg);
    pii edge = beg.second;
    if (link(edge.first, edge.second)) {
      adj[edge.first].push_back(edge.second);
      adj[edge.second].push_back(edge.first);
    }
  }
  sz.resize(n);
  vals = arr;
  dfs(0, 0);
  fill(0, 0);
  for (auto info : infos) cout << info.first.first << ' ' << info.first.second << ' ' << info.second << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  solve();
  return 0;
}
