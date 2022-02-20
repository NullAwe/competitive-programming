#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> colors(n); for (int i = 0; i < n; ++i) cin >> colors[i];
  vector<int> adj[n];
  for (int i = 0; i < n; ++i) {
    vector<int> v;
    adj[i] = v;
  }
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<pair<int, int>> order;
  vector<int> depths(n);
  vector<bool> trav(n, false);
  queue<pair<int, int>> q; q.push({0, 0});
  while (q.size()) {
    pair<int, int> f = q.front(); q.pop();
    order.push_back(f);
    int node = f.second, depth = f.first;
    depths[node] = depth;
    trav[node] = true;
    for (int next : adj[node]) if (!trav[next]) q.push({depth + 1, next});
  }
  sort(order.begin(), order.end());
  reverse(order.begin(), order.end());
  vector<set<int>> sets(n);
  vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    int node = order[i].second;
    set<int> cur;
    sets[node] = cur;
    for (int next : adj[node]) {
      if (depths[next] < depths[node]) continue;
      if (sets[next].size() > sets[node].size()) swap(sets[next], sets[node]);
      for (int num : sets[next]) sets[node].insert(num);
    }
    sets[node].insert(colors[node]);
    ans[node] = sets[node].size();
  }
  // Output:
  for (int num : ans) cout << num << ' ';
  cout << endl;
  return 0;
}
