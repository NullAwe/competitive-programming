#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>

const int MASK = 1 << 17;
const int MAX_VAL = 300000;

int main() {
  int n, m; cin >> n >> m;
  vector<vector<pli>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w; --a, --b;
    adj[a].push_back({w, b});
  }
  vector<ll> d(MAX_VAL, -1); d[0] = d[MASK] = 0;
  set<pli> s; s.insert({0, 0}); s.insert({0, MASK});
  while (s.size()) {
    pli f = *s.begin(); s.erase(s.begin());
    int node = f.second & ~MASK, cut = f.second & MASK; ll dist = f.first;
    for (pli p : adj[node]) {
      int next = p.second | cut, w = p.first;
      if (d[next] >= 0 && d[next] <= dist + w) continue;
      s.erase({d[next], next});
      d[next] = dist + w;
      s.insert({d[next], next});
    }
    if (cut) continue;
    for (pli p : adj[node]) {
      int next = p.second | MASK, w = p.first >> 1;
      if (d[next] >= 0 && d[next] <= dist + w) continue;
      s.erase({d[next], next});
      d[next] = dist + w;
      s.insert({d[next], next});
    }
  }
  cout << d[(n - 1) | MASK] << '\n';
  return 0;
}

