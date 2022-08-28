#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, g;
vector<vector<int>> p, pos;
vector<vector<ll>> l, r;

ll calc(int b, int s, int i) {
  ll ans = l[pos[b][i]][b] + r[pos[b][i + 1]][b];
  for (int bef = 0; bef < g; ++bef)
    if (s & (1 << bef)) ans += 2 * (l[pos[b][i]][bef] + r[pos[b][i + 1]][bef]);
  return ans;
}

int main() {
  string str; cin >> str;
  n = str.size(), g = 0;
  for (int i = 0; i < n; ++i) g = max(g, str[i] - 'A' + 1);
  p = vector<vector<int>>(n + 1, vector<int>(g));
  for (int i = 0; i < n; ++i) p[i + 1] = p[i], ++p[i + 1][str[i] - 'A'];
  l = vector<vector<ll>>(n, vector<ll>(g)), r = vector<vector<ll>>(n, vector<ll>(g));
  vector<vector<ll>> last(g, vector<ll>(g));
  for (int i = 0; i < n; ++i) {
    int val = str[i] - 'A';
    l[i] = last[val];
    for (int j = 0; j < g; ++j) l[i][j] += p[i][j];
    last[val] = l[i];
  }
  last = vector<vector<ll>>(g, vector<ll>(g));
  for (int i = n - 1; i >= 0; --i) {
    int val = str[i] - 'A';
    r[i] = last[val];
    for (int j = 0; j < g; ++j) r[i][j] += p[n][j] - p[i + 1][j];
    last[val] = r[i];
  }
  pos.resize(g);
  for (int i = 0; i < g; ++i) pos[i].push_back(0);
  for (int i = 0; i < n; ++i) pos[str[i] - 'A'].push_back(i);
  for (int i = 0; i < g; ++i) pos[i].push_back(n - 1);
  vector<ll> dp(1 << g, LLONG_MAX); dp[0] = 0;
  for (int mask = 1; mask < (1 << g); ++mask) {
    for (int b = 0; b < g; ++b) {
      if (!(mask & (1 << b))) continue;
      int bef = mask ^ (1 << b), lo = 0, hi = pos[b].size() - 1;
      while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (calc(b, bef, mid - 1) >= calc(b, bef, mid)) lo = mid;
        else hi = mid;
      }
      dp[mask] = min(dp[mask], dp[bef] + calc(b, bef, lo));
    }
  }
  ll ans = dp[(1 << g) - 1];
  cout << ans / 2;
  if (ans & 1) cout << ".5";
  cout << '\n';
  return 0;
}
