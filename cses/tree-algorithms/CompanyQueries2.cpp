#include <bits/stdc++.h>
using namespace std;

const int sz = 30;

vector<vector<int>> adj, up;
vector<int> levels;

inline void dfs(int v, int l) {
  levels[v] = l;
  for (int u : adj[v]) dfs(u, l + 1);
}

inline int query(int v, int u) {
  for (int i = 0; i < sz; ++i) if (u & (1 << i)) v = up[v][i];
  return v;
}

int main() {
  int n, q; cin >> n >> q;
  vector<int> parents(n, 1);
  for (int i = 1; i < n; ++i) cin >> parents[i];
  for (int i = 0; i < n; ++i) --parents[i];
  adj = vector<vector<int>>(n);
  for (int i = 1; i < n; ++i) adj[parents[i]].push_back(i);
  up = vector<vector<int>>(n, vector<int>(sz));
  for (int i = 0; i < n; ++i) up[i][0] = parents[i];
  for (int j = 1; j < sz; ++j) for (int i = 0; i < n; ++i)
    up[i][j] = (up[i][j - 1] >= 0 ? up[up[i][j - 1]][j - 1] : -1);
  levels = vector<int>(n); dfs(0, 0);
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    if (levels[a] > levels[b]) a = query(a, levels[a] - levels[b]);
    else b = query(b, levels[b] - levels[a]);
    if (a == b) {
      cout << a + 1 << '\n';
      continue;
    }
    for (int j = sz - 1; j >= 0; --j) if (up[a][j] != up[b][j]) a = up[a][j], b = up[b][j];
    cout << up[a][0] + 1 << '\n';
  }
  return 0;
}

