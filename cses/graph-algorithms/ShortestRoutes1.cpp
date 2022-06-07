#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>

int main() {
  int n, m; cin >> n >> m;
  vector<vector<pli>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w; --a, --b;
    adj[a].push_back({w, b});
  }
  vector<ll> d(n, -1); d[0] = 0;
  set<pli> s; s.insert({0, 0});
  while (s.size()) {
    pli f = *s.begin(); s.erase(s.begin());
    int node = f.second; ll dist = f.first;
    for (pli p : adj[node]) {
      int next = p.second, w = p.first;
      if (d[next] >= 0 && d[next] <= dist + w) continue;
      s.erase({d[next], next});
      d[next] = dist + w;
      s.insert({d[next], next});
    }
  }
  for (ll num : d) cout << num << ' ';
  cout << '\n';
  return 0;
}
