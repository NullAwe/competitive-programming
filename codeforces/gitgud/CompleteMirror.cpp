#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 1; i < n; ++i) {
    int a, b; cin >> a >> b; --a, --b;
    adj[a].push_back(b); adj[b].push_back(a);
  }
  vector<int> dist(n, -1); dist[0] = 0;
  queue<int> q; q.push(0);
  while (q.size()) {
    int node = q.front(); q.pop();
    for (int next : adj[node]) {
      if (dist[next] >= 0) continue;
      dist[next] = dist[node] + 1;
      q.push(next);
    }
  }
  int m = 0;
  for (int i = 0; i < n; ++i) if (dist[i] > dist[m]) m = i;
  dist = vector<int>(n, -1); dist[m] = 0;
  q.push(m);
  while (q.size()) {
    int node = q.front(); q.pop();
    for (int next : adj[node]) {
      if (dist[next] >= 0) continue;
      dist[next] = dist[node] + 1;
      q.push(next);
    }
  }
  vector<int> todo; todo.push_back(m);
  for (int i = 0; i < n; ++i) if (dist[i] > dist[m]) m = i;
  todo.push_back(m);
  if ((dist[m] & 1) == 0) {
    int temp = m;
    while (dist[temp] != (dist[m] >> 1)) for (int next : adj[temp]) if (dist[next] < dist[temp]) temp = next;
    todo.push_back(temp);
    dist = vector<int>(n, -1); dist[temp] = 0;
    q.push(temp);
    while (q.size()) {
      int node = q.front(); q.pop();
      for (int next : adj[node]) {
        if (dist[next] >= 0) continue;
        dist[next] = dist[node] + 1;
        q.push(next);
      }
    }
    for (int next : adj[temp]) {
      while (adj[next].size() == 2) {
        if (dist[adj[next][0]] > dist[next]) next = adj[next][0];
        else next = adj[next][1];
      }
      if (adj[next].size() > 2) continue;
      if (dist[temp] <= 0) temp = next;
      if (dist[next] < dist[temp]) temp = next;
    }
    if (temp >= 0) todo.push_back(temp);
  }
  for (int start : todo) {
    dist = vector<int>(n, -1); dist[start] = 0;
    q.push(start);
    while (q.size()) {
      int node = q.front(); q.pop();
      for (int next : adj[node]) {
        if (dist[next] >= 0) continue;
        dist[next] = dist[node] + 1;
        q.push(next);
      }
    }
    int md = 0; for (int num : dist) md = max(md, num);
    vector<int> arr(md + 1);
    bool works = true;
    for (int i = 0; i < n; ++i) {
      if (!arr[dist[i]]) arr[dist[i]] = adj[i].size();
      if (adj[i].size() != arr[dist[i]]) {
        works = false;
        break;
      }
    }
    if (works) {
      cout << start + 1 << '\n';
      return 0;
    }
  }
  cout << -1 << '\n';
  return 0;
}
