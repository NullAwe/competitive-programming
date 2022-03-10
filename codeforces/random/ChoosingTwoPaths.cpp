#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

void dfs(int node, int parent, vector<pair<int, int>>& storage) {
  int &ca = storage[node].first, &cb = storage[node].second;
  for (int next : adj[node]) {
    if (next == parent || visited[next]) continue;
    dfs(next, node, storage);
    int b = storage[next].second + 1;
    if (b > cb) ca = cb, cb = b;
    else if (b > ca) ca = b;
  }
  if (cb < 0) cb = 0;
  else if (ca < 0) ca = 0;
}

int main() {
  int n; cin >> n;
  adj = vector<vector<int>>(n);
  visited = vector<bool>(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<int> degree(n); for (int i = 0; i < n; ++i) degree[i] = adj[i].size();
  vector<int> depth(n, -1); depth[0] = 0;
  queue<int> q; q.push(0);
  while (q.size()) {
    int node = q.front(); q.pop();
    for (int next : adj[node]) {
      if (depth[next] >= 0) continue;
      depth[next] = depth[node] + 1;
      q.push(next);
    }
  }
  vector<pair<int, int>> storage(n);
  dfs(0, -1, storage);
  vector<pair<int, int>> values(n);
  for (int i = 0; i < n; ++i) if (degree[i] >= 3) values[i] = {depth[i], storage[i].first + storage[i].second};
  int ind = 0;
  for (int i = 0; i < n; ++i) if (values[i].first > values[ind].first ||
      (values[i].first == values[ind].first && values[i].second > values[ind].second)) ind = i;
  if (ind == 0) {
    vector<pair<int, int>> leaves;
    for (int i = 0; i < n; ++i) if (degree[i] == 1) leaves.push_back({depth[i], i + 1});
    sort(leaves.begin(), leaves.end());
    int sz = leaves.size();
    cout << leaves[sz - 1].second << ' ' << leaves[sz - 2].second << '\n' << leaves[sz - 3].second << ' ' << leaves[sz - 3].second << '\n';
    return 0;
  }
  bool done1 = false, done2 = false;
  for (int next : adj[ind]) {
    if (!done1 && storage[next].second == storage[ind].first - 1) {
      q.push(next);
      done1 = true;
    } else if (!done2 && storage[next].second == storage[ind].second - 1) {
      q.push(next);
      done2 = true;
    }
  }
  vector<int> ans;
  while (q.size()) {
    int node = q.front(); q.pop();
    visited[node] = true;
    if (degree[node] == 1) {
      ans.push_back(node + 1);
      continue;
    }
    for (int next : adj[node]) {
      if (storage[next].second == storage[node].second - 1) {
        q.push(next);
        break;
      }
    }
  }
  depth = vector<int>(n, -1); depth[ind] = 0;
  q.push(ind);
  while (q.size()) {
    int node = q.front(); q.pop();
    for (int next : adj[node]) {
      if (depth[next] >= 0) continue;
      depth[next] = depth[node] + 1;
      q.push(next);
    }
  }
  storage = vector<pair<int, int>>(n, {-1, -1});
  dfs(ind, -1, storage);
  values = vector<pair<int, int>>(n);
  for (int i = 0; i < n; ++i) if (degree[i] >= 3 && !visited[i]) values[i] = {depth[i], storage[i].first + storage[i].second};
  for (int i = 0; i < n; ++i) if (values[i].first > values[ind].first ||
      (values[i].first == values[ind].first && values[i].second > values[ind].second)) ind = i;
  done1 = false, done2 = false;
  for (int next : adj[ind]) {
    if (!done1 && storage[next].second == storage[ind].first - 1) {
      q.push(next);
      done1 = true;
    } else if (!done2 && storage[next].second == storage[ind].second - 1) {
      q.push(next);
      done2 = true;
    }
  }
  while (q.size()) {
    int node = q.front(); q.pop();
    if (degree[node] == 1) {
      ans.push_back(node + 1);
      continue;
    }
    for (int next : adj[node]) {
      if (storage[next].second == storage[node].second - 1) {
        q.push(next);
        break;
      }
    }
  }
  cout << ans[0] << ' ' << ans[2] << '\n' << ans[1] << ' ' << ans[3] << '\n';
  return 0;
}
