#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<set<int>> adj, rev;
ll ans = 0;

vector<int> r, p;

int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

void link(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return;
  if (r[a] < r[b]) swap(a,b);
  if (r[a] == r[b]) ++r[a];
  p[b] = a;
}

int main() {
  int n, m; cin >> n >> m;
  r = vector<int>(n), p = vector<int>(n); for(int i = 0; i < n; ++i) p[i] = i;
  adj.resize(n), rev.resize(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b; if (a > b) swap(a, b);
    adj[a].insert(b), rev[b].insert(a);
  }
  for (int i = 0; i < n; ++i) {
    for (int num : rev[i]) {
      if (find(i) == find(num)) continue;
      int p = find(num), pp = find(i);
      link(p, pp);
      int np = find(p);
      if (adj[p].size() < adj[pp].size()) swap(adj[p], adj[pp]);
      for (int x : adj[pp]) adj[p].insert(x);
      adj[p].erase(i);
      swap(adj[p], adj[np]);
    }
    ans += adj[find(i)].size();
  }
  cout << ans - m << '\n';
  return 0;
}
