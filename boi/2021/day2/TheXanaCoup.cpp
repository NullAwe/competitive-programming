#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define vvi vector<vi>

vvi adj;
vi on;

vvi dfs(int v, int p) {
  vvi ans = vvi(2, vi(2, -1));
  bool start = false;
  for (int u : adj[v]) {
    if (u == p) continue;
    vvi res = dfs(u, v);
    if (!start) {
      ans = res, start = true;
      continue;
    }
    vvi nxt = vvi(2, vi(2, INT_MAX));
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j)
        if (min(ans[i][j], res[i][j]) >= 0)
          nxt[i][0] = min(nxt[i][0], ans[i][j] + res[i][j]);
      for (int j = 0; j < 2; ++j)
        if (min(ans[i][j], res[i][1 - j]) >= 0)
          nxt[i][1] = min(nxt[i][1], ans[i][j] + res[i][1 - j]);
    }
    for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j)
      if (nxt[i][j] == INT_MAX) nxt[i][j] = -1;
    ans = nxt;
  }
  if (!start) ans[0][0] = ans[1][0] = 0;
  vvi copy = ans;
  if (on[v]) swap(copy[0][0], copy[0][1]), swap(copy[1][0], copy[1][1]);
  ans[0][0] = copy[0][0], ans[0][1] = copy[1][1] < 0 ? -1 : copy[1][1] + 1;
  ans[1][0] = copy[0][1], ans[1][1] = copy[1][0] < 0 ? -1 : copy[1][0] + 1;
  return ans;
}

int main() {
  int n; cin >> n;
  adj.resize(n), on.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  for (int i = 0; i < n; ++i) cin >> on[i];
  vi res = dfs(0, 0)[0];
  int ans = res[0] < 0 || res[1] < 0 ? max(res[0], res[1]) : min(res[0], res[1]);
  cout << (ans < 0 ? "impossible" : to_string(ans)) << '\n';
}
