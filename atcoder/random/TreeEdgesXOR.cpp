#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

int main() {
  int n; cin >> n;
  vector<pair<int, pii>> adj[n];
  for (int i = 0; i < n - 1; ++i) {
    int a, b, x, y; cin >> a >> b >> x >> y; --a, --b;
    adj[a].push_back({b, {x, y}});
    adj[b].push_back({a, {x, y}});
  }
  vector<int> d1(n), d2(n);
  vector<bool> vis(n);
  queue<int> q; q.push(0); vis[0] = true;
  while (q.size()) {
    int v = q.front(); q.pop();
    for (pair<int, pii> p : adj[v]) {
      if (vis[p.first]) continue;
      q.push(p.first); vis[p.first] = true;
      d1[p.first] = d1[v] ^ p.second.first;
      d2[p.first] = d2[v] ^ p.second.second;
    }
  }
  int _xor = 0;
  for (int num : d1) _xor ^= num;
  for (int num : d2) _xor ^= num;
  for (int i = 0; i < n; ++i) d1[i] ^= _xor;
  sort(d1.begin(), d1.end());
  sort(d2.begin(), d2.end());
  if (d1 == d2) cout << "YES\n";
  else cout << "NO\n";
  return 0;
}