#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> p;

int find(int a) {
  return a == p[a] ? a : p[a] = find(p[a]);
}

void link(int a, int b) {
  p[find(b)] = find(a);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  p.resize(n); for (int i = 0; i < n; ++i) p[i] = i;
  vector<set<int>> adj(n), rev(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].insert(b), rev[b].insert(a);
  }
  vector<int> alive(n);
  set<pii> ae;
  for (int i = 0; i < n; ++i) alive[i] = adj[i].size(), ae.insert({alive[i], i});
  while (ae.size()) {
    pii beg = *ae.begin(); ae.erase(beg);
    if (beg.first) break;
    for (int from : rev[beg.second]) ae.erase({alive[from], from}), ae.insert({--alive[from], from});
  }
  for (int i = 0; i < n; ++i) if (!alive[i]) for (int from : rev[i]) adj[from].erase(i);
  vector<int> deg(n);
  set<pii> degs;
  set<int> cur;
  for (int i = 0; i < n; ++i) if (alive[i]) deg[i] = adj[i].size(), degs.insert({deg[i], i}), cur.insert(i);
  while (degs.size()) {
    pii beg = *degs.begin(); degs.erase(beg), cur.erase(beg.second);
    if (beg.first > 1) break;
    int into = *adj[beg.second].begin();
    if (beg.second == into) continue;
    if (find(into) != into) exit(0);
    bool self = adj[into].count(beg.second) || adj[into].count(into);
    if (rev[beg.second].size() < rev[into].size()) {
      link(into, beg.second);
      for (int from : rev[beg.second]) {
        int real = find(from);
        adj[real].erase(beg.second), adj[real].insert(into);
        if (cur.count(real)) degs.erase({deg[real], real}), degs.insert({deg[real] = adj[real].size(), real});
      }
      for (int from : rev[beg.second]) rev[into].insert(from);
      rev[into].erase(beg.second), adj[into].erase(beg.second);
      if (!self) rev[into].erase(into), adj[into].erase(into);
      if (cur.count(into)) degs.erase({deg[into], into}), degs.insert({deg[into] = adj[into].size(), into});
    } else {
      link(beg.second, into);
      for (int from : rev[into]) {
        if (from == beg.second) continue;
        int real = find(from);
        adj[real].erase(into), adj[real].insert(beg.second);
        if (cur.count(real)) degs.erase({deg[real], real}), degs.insert({deg[real] = adj[real].size(), real});
      }
      swap(adj[beg.second], adj[into]);
	  if (adj[beg.second].count(into)) rev[beg.second].insert(beg.second), adj[beg.second].insert(beg.second);
	  rev[beg.second].erase(into), adj[beg.second].erase(into);
      if (!self) rev[beg.second].erase(beg.second), adj[beg.second].erase(beg.second);
      for (int from : rev[into]) rev[beg.second].insert(from);
      if (cur.count(into)) degs.erase({deg[into], into}), degs.insert({deg[beg.second] = adj[beg.second].size(), beg.second}),
        cur.erase(into), cur.insert(beg.second);
    }
  }
  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    cout << (find(a) == find(b) || !alive[a] || !alive[b] ? 'B' : 'H');
  }
  cout << '\n';
  return 0;
}
