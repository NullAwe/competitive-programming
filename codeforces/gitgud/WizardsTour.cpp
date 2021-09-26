#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX_N = 200001;

vector<vector<int>> ans;

ll getVal(ll a, ll b) { return a * MAX_N + b; }

void dfs(int node, vector<vector<int>>& adj, set<int>& used, set<ll>& edges) {
  used.insert(node);
  for (int next : adj[node]) {
    if (!used.count(next)) {
      edges.insert(getVal(node, next));
      edges.insert(getVal(next, node));
      dfs(next, adj, used, edges);
      bool done = false;
      for (int nn : adj[next]) {
        if (!edges.count(getVal(next, nn))) {
          edges.insert(getVal(next, nn));
          edges.insert(getVal(nn, next));
          done = true;
          vector<int> row = {node + 1, next + 1, nn + 1};
          ans.push_back(row);
          break;
        }
      }
      if (!done) {
        edges.erase(getVal(node, next));
        edges.erase(getVal(next, node));
      }
    }
  }
  int last = -1;
  for (int next : adj[node]) {
    if (!edges.count(getVal(node, next))) {
      if (last < 0) last = next;
      else {
        edges.insert(getVal(node, last));
        edges.insert(getVal(node, next));
        edges.insert(getVal(last, node));
        edges.insert(getVal(next, node));
        vector<int> row = {last + 1, node + 1, next + 1};
        ans.push_back(row);
        last = -1;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b;
    --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  set<int> used;
  set<ll> edges;
  for (int i = 0; i < n; ++i) dfs(i, adj, used, edges);
  // Output:
  cout << ans.size() << endl;
  for (vector<int> row : ans)
    cout << row[0] << ' ' << row[1] << ' ' << row[2] << endl;
  return 0;
}