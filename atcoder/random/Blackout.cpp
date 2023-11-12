#include <bits/stdc++.h>
using namespace std;

int n, sum = 0;
vector<vector<int>> adj, rev;
vector<bool> vis;
vector<int> color, comp;

bool dfs(int v, int c) {
  if (color[v] >= 0) return color[v] == c;
  color[v] = c;
  comp.push_back(v);
  bool can = true;
  sum += adj[v].size();
  for (int u : adj[v]) can &= dfs(u, (c + 1) % 3);
  for (int u : rev[v]) can &= dfs(u, (c + 2) % 3);
  return can;
}

int main() {
  cin >> n;
  int m; cin >> m;
  adj.resize(n), rev.resize(n), color.resize(n, -1);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    rev[b].push_back(a);
  }
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    if (color[i] >= 0) continue;
    bool can = dfs(i, 0);
    if (can) {
      vector<long long> cnt(3);
      for (int v : comp) ++cnt[color[v]];
      if (min(cnt[0], min(cnt[1], cnt[2])) == 0) ans += sum;
      else ans += cnt[0] * cnt[1] + cnt[1] * cnt[2] + cnt[2] * cnt[0];
    } else ans += (long long) comp.size() * (long long) comp.size();
    comp.clear();
    sum = 0;
  }
  cout << ans << '\n';
  return 0;
}