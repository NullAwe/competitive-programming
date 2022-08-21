#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MOD = 1e9 + 7;

vector<int> r, p;

int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

void link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return;
  if (r[a] < r[b]) swap(a, b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
}

vector<set<int>> adj, rev;

ll solve(int v) {
  ll ans = 1;
  for (int u : adj[v]) ans = ans * solve(find(u)) % MOD;
  return (ans + 1) % MOD;
}

int main() {
  ifstream cin("cave.in");
  ofstream cout("cave.out");
  int n, m; cin >> n >> m;
  int grid[n][m], id = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) grid[i][j] = -1;
  for (int i = 0; i < n; ++i) {
    string str; cin >> str;
    for (int j = 0; j < m; ++j) {
      if (str[j] == '#') continue;
      if (!j || grid[i][j - 1] < 0) grid[i][j] = id++;
      else grid[i][j] = grid[i][j - 1];
    }
  }
  adj.resize(id), rev.resize(id);
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < m; ++j) {
      int a = grid[i][j], b = grid[i + 1][j];
      if (a < 0 || b < 0) continue;
      adj[a].insert(b), rev[b].insert(a);
    }
  }
  vector<bool> merged(id);
  r.resize(id), p.resize(id); for (int i = 0; i < id; ++i) p[i] = i;
  for (int v = id - 1; v >= 0; --v) {
    if (v != find(v) || !rev[v].size()) continue;
    set<int> ns; for (int num : rev[v]) ns.insert(find(num));
    rev[v] = ns;
    if (ns.size() == 1 && merged[*ns.begin()]) continue;
    int first = *rev[v].begin();
    for (int num : rev[v]) link(first, num);
    first = find(first);
    set<int> nr, na;
    for (int u : rev[v]) {
      for (int num : rev[u]) nr.insert(find(num));
      for (int num : adj[u]) na.insert(find(num));
    }
    rev[v].clear(), rev[v].insert(first), rev[first] = nr, adj[first] = na, merged[first] = true;
  }
  ll ans = 1;
  for (int v = 0; v < id; ++v) if (v == find(v) && !rev[v].size()) ans = ans * solve(v) % MOD;
  cout << ans << '\n';
  return 0;
}

