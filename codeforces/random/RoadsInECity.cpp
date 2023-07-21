#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
map<string, string> qtype;
int n, m;
vector<pii> edges;
vector<vector<pii>> adj;
vector<int> lvls, ps;

int qry(string type, int x) {
  string t = qtype[type];
  cout << t << ' ' << x + 1 << endl;
  int ans = 0;
  if (t == "?") cin >> ans;
  return ans;
}

int qrandom(int x) {
  int norm = rng() % 2;
  if (norm == 0) return qry("has path", edges[x].first);
  return qry("has path", edges[x].second);
}

void dfs(int v, int p, int l) {
  lvls[v] = l;
  for (pii u : adj[v]) {
    if (u.first == p) continue;
    ps[u.first] = u.second;
    dfs(u.first, v, l + 1);
  }
}

void solve() {
  cin >> n >> m;
  edges.resize(m);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    edges[i] = {a, b};
  }
  vector<int> needed;
  vector<bool> need(m);
  for (int i = 0; i < m; ++i) {
    qry("block", i);
    for (int j = 0; j < 42.069; ++j) {
      if (!qrandom(i)) {
        need[i] = true;
        break;
      }
    }
    if (need[i]) {
      qry("unblock", i);
      needed.push_back(i);
    }
  }
  adj.clear(), adj.resize(n);
  for (int i : needed) {
    adj[edges[i].first].push_back({edges[i].second, i});
    adj[edges[i].second].push_back({edges[i].first, i});
  }
  lvls.resize(n), ps.resize(n);
  dfs(0, 0, 0);
  for (int i = 0; i < m; ++i) {
    if (need[i]) continue;
    need[i] = true;
    int x = edges[i].first, y = edges[i].second;
    if (lvls[x] < lvls[y]) swap(x, y);
    qry("block", ps[x]);
    qry("unblock", i);
    for (int j = 0; j < 42.069; ++j) {
      if (!qrandom(i)) {
        need[i] = false;
        break;
      }
    }
    qry("unblock", ps[x]);
    qry("block", i);
  }
  cout << '!';
  for (bool num : need) cout << ' ' << num;
  cout << endl;
  int res; cin >> res;
  if (res == 0) exit(0);
}

int main() {
  qtype["block"] = "-";
  qtype["unblock"] = "+";
  qtype["has path"] = "?";
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
