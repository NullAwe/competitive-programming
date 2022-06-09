#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<vector<int>> adj, rev;
vector<bool> vis;
vector<int> order, comp;

void dfs(int v) {
  if (vis[v]) return;
  vis[v] = true;
  for (int u : adj[v]) dfs(u);
  order.push_back(v);
}

void gc(int v, int c) {
  if (vis[v]) return;
  vis[v] = true, comp[v] = c;
  for (int u : rev[v]) gc(u, c);
}

int main() {
  int n, m; cin >> n >> m;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  adj = vector<vector<int>>(n), rev = vector<vector<int>>(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    rev[b].push_back(a);
  }
  vis = vector<bool>(n);
  for (int i = 0; i < n; ++i) dfs(i);
  vis = vector<bool>(n);
  comp = vector<int>(n);
  reverse(order.begin(), order.end());
  int c = 0;
  for (int v : order) {
    if (vis[v]) continue;
    gc(v, c++);
  }
  vector<vector<int>> ccadj(c);
  for (int i = 0; i < n; ++i) for (int v : adj[i]) ccadj[comp[i]].push_back(comp[v]);
  vector<ll> val(c); for (int i = 0; i < n; ++i) val[comp[i]] += arr[i];
  vector<ll> dp(c);
  for (int i = c - 1; i >= 0; --i) {
    for (int v : ccadj[i]) dp[i] = max(dp[i], dp[v]);
    dp[i] += val[i];
  }
  ll ans = 0;
  for (ll num : dp) ans = max(ans, num);
  cout << ans << '\n';
  return 0;
}

