#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>

int main() {
  int n, m, k; cin >> n >> m >> k;
  vector<vector<pli>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w;
    adj[a - 1].push_back({w, b - 1});
  }
  vector<multiset<ll>> d(n); d[0].insert(0);
  multiset<pli> s; s.insert({0, 0});
  while (s.size()) {
    pli f = *s.begin(); s.erase(s.begin());
    for (pli p : adj[f.second]) {
      int next = p.second;
      ll w = p.first + f.first;
      if (d[next].size() < k) {
        d[next].insert(w);
        s.insert({w, next});
      } else if (d[next].upper_bound(w) != d[next].end()) {
        ll lw = *--d[next].end(); d[next].erase(--d[next].end()); d[next].insert(w);
        s.erase(s.find({lw, next})); s.insert({w, next});
      }
    }
  }
  for (ll num : d[n - 1]) cout << num << ' ';
  cout << '\n';
  return 0;
}
