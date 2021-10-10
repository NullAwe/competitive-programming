#include <bits/stdc++.h>
using namespace std;

int getImposters(int node, vector<vector<pair<int, int>>>& adj,
                vector<vector<pair<int, int>>>& back, vector<int>& status) {
  int imposters = 0;
  if (status[node]) imposters = 1;
  for (pair<int, int> next : adj[node]) {
    int nextVal = (status[node] ^ next.second);
    if (status[next.first] >= 0 && status[next.first] != nextVal) {
      return -1;
    }
    if (status[next.first] < 0) {
      status[next.first] = nextVal;
      int num = next.first;
      int next = getImposters(num, adj, back, status);
      if (next == -1) return -1;
      imposters += next;
    }
  }
  for (pair<int, int> next : back[node]) {
    int nextVal = (status[node] ^ next.second);
    if (status[next.first] >= 0 && status[next.first] != nextVal) {
      return -1;
    }
    if (status[next.first] < 0) {
      status[next.first] = nextVal;
      int num = next.first;
      int next = getImposters(num, adj, back, status);
      if (next == -1) return -1;
      imposters += next;
    }
  }
  return imposters;
}

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<pair<int, int>>> adj(n);
  vector<vector<pair<int, int>>> back(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b;
    --a; --b;
    string status; cin >> status;
    if (status[0] == 'i') {
      adj[a].push_back({b, 1});
      back[b].push_back({a, 1});
    } else {
      adj[a].push_back({b, 0});
      back[b].push_back({a, 0});
    }
  }
  vector<int> status(n, -1);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (status[i] >= 0) continue;
    vector<bool> done(n, false);
    vector<int> in;
    queue<int> q;
    q.push(i);
    done[i] = true;
    in.push_back(i);
    while (q.size()) {
      int node = q.front(); q.pop();
      for (pair<int, int> p : adj[node]) {
        if (done[p.first]) continue;
        done[p.first] = true;
        in.push_back(p.first);
        q.push(p.first);
      }
      for (pair<int, int> p : back[node]) {
        if (done[p.first]) continue;
        done[p.first] = true;
        in.push_back(p.first);
        q.push(p.first);
      }
    }
    status[i] = 0;
    int imposters = getImposters(i, adj, back, status);
    for (int num : in) status[num] = -1;
    status[i] = 1;
    imposters = max(imposters, getImposters(i, adj, back, status));
    if (imposters == -1) {
      // Output:
      cout << -1 << endl;
      return;
    }
    ans += imposters;
  }
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
