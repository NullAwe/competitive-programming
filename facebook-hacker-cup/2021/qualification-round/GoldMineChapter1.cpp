#include <bits/stdc++.h>
using namespace std;

int get(int node, vector<int>& weights, vector<int>& fill, vector<vector<int>>& adj) {
  int m = 0;
  for (int next : adj[node]) m = max(m, get(next, weights, fill, adj));
  fill[node] = weights[node] + m;
  return fill[node];
}

int main() {
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n; cin >> n;
    vector<int> arr(n); for (int j = 0; j < n; ++j) cin >> arr[j];
    // Output for a corner case:
    if (n == 1) {
      cout << "Case #" << i << ": " << arr[0] << endl;
      continue;
    }
    vector<vector<int>> adj(n);
    for (int j = 1; j < n; ++j) {
      int a, b; cin >> a >> b;
      --a; --b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    // Creates the tree from the graph:
    vector<vector<int>> fixed(n);
    vector<bool> trav(n);
    queue<int> q;
    q.push(0);
    trav[0] = true;
    while (!q.empty()) {
      int node = q.front(); q.pop();
      for (int next : adj[node]) {
        if (trav[next]) continue;
        trav[next] = true;
        fixed[node].push_back(next);
        q.push(next);
      }
    }
    // Finds maximum amount of gold along each path:
    vector<int> fill(n);
    get(0, arr, fill, fixed);
    vector<int> children;
    for (int next : fixed[0]) children.push_back(fill[next]);
    sort(children.begin(), children.end());
    // Travels to two leaves with maximum gold along the path:
    int sum = children[children.size() - 1] + arr[0];
    if (children.size() > 1) sum += children[children.size() - 2];
    // Output:
    cout << "Case #" << i << ": " << sum << endl;
  }
}
