#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n, m;
  cin >> n >> m;
  vector<int> lengths(n);
  vector<vector<int>> adjList(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adjList[a - 1].push_back(b - 1);
    adjList[b - 1].push_back(a - 1);
  }
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (int next : adjList[node]) {
      if (next == 0 || lengths[next] > 0) continue;
      lengths[next] = lengths[node] + 1;
      q.push(next);
    }
  }
  if (lengths[n - 1] == 0) {
    cout << "IMPOSSIBLE";
  } else {
    cout << lengths[n - 1] + 1 << "\n";
    vector<int> path(lengths[n - 1] + 1);
    path[lengths[n - 1]] = n;
    int node = n - 1;
    for (int i = lengths[n - 1] - 1; i >= 0; --i) {
      for (int next : adjList[node]) {
        if (lengths[next] == i) {
          node = next;
          break;
        }
      }
      path[i] = node + 1;
    }
    for (int node : path) cout << node << " ";
  }
  return 0;
}
