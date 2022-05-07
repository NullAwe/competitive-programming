#include <bits/stdc++.h>
using namespace std;

vector<int> getPath(vector<vector<int>> adj, int n) {
  vector<multiset<int>> g(n);
  for (int i = 0; i < n; ++i) for (int j : adj[i]) g[i].insert(j);
  vector<int> deg(n); for (int i = 0; i < n; ++i) deg[i] = g[i].size();
  int first = 0;
  while (first < n && !deg[first]) ++first;
  if (first == n) return vector<int>(0);
  int v1 = -1, v2 = -1;
  bool bad = false;
  for (int i = 0; i < n; ++i) {
    if (deg[i] & 1) {
      if (v1 == -1) v1 = i;
      else if (v2 == -1) v2 = i;
      else bad = true;
    }
  }
  if (v1 != -1) g[v1].insert(v2), g[v2].insert(v1);
  stack<int> st;
  st.push(first);
  vector<int> res;
  while (!st.empty()) {
    int v = st.top();
    if (g[v].size() == 0) {
      res.push_back(v);
      st.pop();
    } else {
      int i = *g[v].begin();
      g[v].erase(g[v].lower_bound(i));
      g[i].erase(g[i].lower_bound(v));
      st.push(i);
    }
  }
  if (v1 != -1) {
    for (size_t i = 0; i + 1 < res.size(); ++i) {
      if ((res[i] == v1 && res[i + 1] == v2) ||
          (res[i] == v2 && res[i + 1] == v1)) {
        vector<int> res2;
        for (size_t j = i + 1; j < res.size(); ++j) res2.push_back(res[j]);
        for (size_t j = 1; j <= i; ++j) res2.push_back(res[j]);
        res = res2;
        break;
      }
    }
  }
  for (int i = 0; i < n; ++i) if (g[i].size()) bad = true;
  if (bad) return vector<int>(0);
  return res;
}

int main() {
  int n; cin >> n; --n;
  vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
  vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
  for (int i = 0; i < n; ++i) {
    if (a[i] > b[i]) {
      cout << "-1\n";
      return 0;
    }
  }
  int cur = 1;
  map<int, int> id;
  for (int i = 0; i < n; ++i) {
    if (id[a[i]] == 0) id[a[i]] = cur++;
    if (id[b[i]] == 0) id[b[i]] = cur++;
  }
  vector<int> back(cur);
  for (int i = 0; i < n; ++i) {
    back[id[a[i]]] = a[i];
    back[id[b[i]]] = b[i];
  }
  vector<vector<int>> adj(cur);
  for (int i = 0; i < n; ++i) {
    adj[id[a[i]]].push_back(id[b[i]]);
    adj[id[b[i]]].push_back(id[a[i]]);
  }
  vector<int> path = getPath(adj, cur);
  if (path.size() == 0) cout << -1;
  else for (int num : path) cout << back[num] << ' ';
  cout << '\n';
  return 0;
}
