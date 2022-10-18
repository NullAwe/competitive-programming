#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>

vector<vector<int>> adj;
vector<ll> c;

pll dfs(int v, int k, int k2) {
  int nc = adj[v].size();
  if (!nc) return {c[v] * k, c[v] * k2};
  int a = k / nc, b = k2 / nc + (k2 % nc > 0);
  vector<pll> nexts(nc);
  for (int i = 0; i < nc; ++i) nexts[i] = dfs(adj[v][i], a, b);
  vector<ll> diffs(nc);
  for (int i = 0; i < nc; ++i) diffs[i] = nexts[i].second - nexts[i].first;
  sort(diffs.begin(), diffs.end());
  pll ans = {c[v] * k, c[v] * k2};
  for (pll next : nexts) ans.first += next.first, ans.second += next.first;
  for (int i = 0; i < k % nc; ++i) ans.first += diffs[nc - 1 - i];
  for (int i = 0; i < k2 % nc; ++i) ans.second += diffs[nc - 1 - i];
  if (k2 % nc == 0) for (ll num : diffs) ans.second += num;
  return ans;
}

void solve() {
  int n, k; cin >> n >> k;
  adj = vector<vector<int>>(n);
  for (int i = 1; i < n; ++i) {
    int p; cin >> p; --p;
    adj[p].push_back(i);
  }
  c = vector<ll>(n);
  for (int i = 0; i < n; ++i) cin >> c[i];
  cout << dfs(0, k, k).first << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
