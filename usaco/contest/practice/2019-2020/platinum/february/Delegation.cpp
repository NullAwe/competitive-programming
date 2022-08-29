#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

int n;
vector<vector<int>> adj;
vector<int> dp;

ifstream in("deleg.in");
ofstream out("deleg.out");

bool dfs(int v, int p, int len) {
  if (adj[v].size() == 1 && v != p) return true;
  for (int u : adj[v]) if (u != p && !dfs(u, v, len)) return false;
  multiset<int> dps;
  for (int u : adj[v]) if (u != p) dps.insert(dp[u] + 1);
  if (dps.size() == 1) {
    if (!v && *dps.begin() < len) return false;
    return dp[v] = *dps.begin();
  }
  multiset<int> rem;
  while (dps.size() > 2 || (dps.size() > 1 && rem.size())) {
    int small = *dps.begin(); dps.erase(dps.find(small));
    if (small >= len) break;
    auto it = dps.lower_bound(len - small);
    if (it == dps.end()) {
      rem.insert(small);
      continue;
    }
    dps.erase(it);
  }
  for (int num : rem) dps.insert(num);
  if (dps.size() > 2 && *dps.begin() < len) return false;
  if (dps.size() == 2 && *dps.begin() + *--dps.end() < len) return false;
  if (!v && dps.size() == 1 && *dps.begin() < len) return false;
  if (dps.size() == 2 && *--dps.end() < len) return 1 - (dp[v] = 0);
  return dp[v] = *dps.begin();
}

bool possible(int len) {
  dp = vector<int>(n);
  return dfs(0, 0, len);
}

int main() {
  in >> n;
  adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; in >> a >> b; --a, --b;
    adj[a].push_back(b), adj[b].push_back(a);
  }
  int lo = 1, hi = n;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    if (possible(mid)) lo = mid;
    else hi = mid;
  }
  out << lo << '\n';
  return 0;
}
