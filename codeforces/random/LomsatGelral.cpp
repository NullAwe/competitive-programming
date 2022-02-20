#include <bits/stdc++.h>
using namespace std;

#define ll long long

void initialize(map<int, ll>& m, int key) {
  if (m.find(key) == m.end()) {
    m[key] = 0;
  }
}

void initialize(map<int, int>& m, int key) {
  if (m.find(key) == m.end()) {
    m[key] = 0;
  }
}

int main() {
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
  vector<pair<map<int, ll>, map<int, int>>> maps(n);
  vector<ll> ans(n);
  for (int i = 0; i < n; ++i) {
    int node = order[i].second;
    map<int, ll> a;
    map<int, int> b;
    maps[node] = {a, b};
    for (int next : adj[node]) {
      if (depths[next] < depths[node]) continue;
      if (maps[next].second.size() > maps[node].second.size()) swap(maps[next], maps[node]);
      for (auto& p : maps[next].second) {
        int color = p.first, num = p.second;
        initialize(maps[node].second, color);
        initialize(maps[node].first, maps[node].second[color]);
        maps[node].first[maps[node].second[color]] -= color;
        maps[node].second[color] += num;
        num = maps[node].second[color];
        initialize(maps[node].first, num);
        maps[node].first[num] += color;
      }
    }
    initialize(maps[node].second, colors[node]);
    initialize(maps[node].first, maps[node].second[colors[node]]);
    maps[node].first[maps[node].second[colors[node]]] -= colors[node];
    ++maps[node].second[colors[node]];
    initialize(maps[node].first, maps[node].second[colors[node]]);
    maps[node].first[maps[node].second[colors[node]]] += colors[node];
    auto it = maps[node].first.end(); --it;
    ans[node] = it->second;
  }
  // Output:
  for (ll num : ans) cout << num << ' ';
  cout << endl;
  return 0;
}
