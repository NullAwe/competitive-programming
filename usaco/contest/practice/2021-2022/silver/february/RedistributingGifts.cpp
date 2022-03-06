#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<vector<int>> arr(n, vector<int>(n)); for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> arr[i][j];
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) --arr[i][j];
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; ++i) {
    vector<int> from;
    for (int j = 0; j < n; ++j) {
      if (arr[i][j] == i) break;
      from.push_back(arr[i][j]);
    }
    for (int node : from) adj[node].push_back(i);
  }
  for (int i = 0; i < n; ++i) {
    vector<bool> trav(n);
    queue<int> q;
    q.push(i); trav[i] = true;
    while (q.size()) {
      int node = q.front(); q.pop();
      for (int next : adj[node]) {
        if (!trav[next]) {
          q.push(next); trav[next] = true;
        }
      }
    }
    for (int j = 0; j < n; ++j) {
      if (trav[arr[i][j]]) {
        cout << arr[i][j] + 1 << '\n';
        break;
      }
    }
  }
  return 0;
}
