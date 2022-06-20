#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n;

vector<vector<int>> adj;
vector<int> subs;
vector<ll> sums;

inline void dfs(int v, int p) { for (int u : adj[v]) if (u != p) dfs(u, v), sums[v] += sums[u] + subs[u], subs[v] += subs[u]; }

inline void dfs2(int v, int p) {
  if (v) sums[v] = sums[p] + n - 2 * subs[v];
  for (int u : adj[v]) if (u != p) dfs2(u, v);
}

int main() {
  cin >> n;
  adj = vector<vector<int>>(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  subs = vector<int>(n, 1);
  sums = vector<ll>(n);
  dfs(0, 0); dfs2(0, 0);
  for (ll sum : sums) cout << sum << ' ';
  cout << '\n';
  return 0;
}

