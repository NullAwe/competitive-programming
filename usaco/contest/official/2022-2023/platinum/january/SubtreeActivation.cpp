#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define plll pair<pair<ll, ll>, ll>

int n;
vector<vector<int>> adj;
vector<int> depth, sz;

int dfs1(int v) {
  sz[v] = 1;
  for (int u : adj[v]) depth[v] = max(depth[v], dfs1(u) + 1);
  for (int u : adj[v]) sz[v] += sz[u];
  return depth[v];
}

plll dfs2(int v) {
  vector<pll> nexts;
  vector<ll> nw;
  vector<pll> weird;
  vector<pll> saved;
  int ind = 0;
  for (int u : adj[v]) {
    plll nxt = dfs2(u);
    pll act = nxt.first;
    nw.push_back(nxt.second);
    weird.push_back({act.second - nxt.second, ind});
    nexts.push_back(act);
    saved.push_back({act.second - act.first, ind});
    ++ind;
  }
  sort(saved.begin(), saved.end());
  reverse(saved.begin(), saved.end());
  ll ans = 0;
  for (int i = 0; i < saved.size(); ++i) {
    if (i < 2) ans += nexts[saved[i].second].first;
    else ans += nexts[saved[i].second].second;
  }
  sort(weird.begin(), weird.end());
  reverse(weird.begin(), weird.end());
  ll ans2 = 0;
  for (int i = 0; i < weird.size(); ++i) {
    if (i < 1) ans2 += nw[weird[i].second];
    else ans2 += nexts[weird[i].second].second;
  }
  ll first = min(ans, ans2) + 2 * sz[v];
  ll third = first - 2 * sz[v];
  ans = 0;
  for (int i = 0; i < saved.size(); ++i) {
    if (i < 1) ans += nexts[saved[i].second].first;
    else ans += nexts[saved[i].second].second;
  }
  ll second = ans;
  return {{second, first}, third};
}

int main() {
  cin >> n;
  adj.resize(n);
  for (int i = 1; i < n; ++i) {
    int p; cin >> p; --p;
    adj[p].push_back(i);
  }
  depth.resize(n), sz.resize(n); dfs1(0);
  cout << dfs2(0).first.second << '\n';
  return 0;
}
