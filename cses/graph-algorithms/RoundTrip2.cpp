#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> edge(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    edge[a].push_back(b);
  }
  // Topological sort using dfs:
  vector<bool> done(n), inStack(n);
  stack<int> s, path;
  int small = 0;
  while (true) {
    // Go to the next untraveled node for dfs:
    if (s.empty()) {
      while (small < n && done[small]) ++small;
      if (small < n) s.push(small);
    }
    if (s.empty()) break; // We are done, no cycles.
    // Add top node into the "path":
    int node = s.top();
    if (done[node]) {
      s.pop();
      inStack[node] = false;
      path.pop();
      continue;
    }
    inStack[node] = true;
    path.push(node);
    // Look through neighbors:
    int size = s.size();
    for (int next : edge[node]) {
      if (inStack[next]) {
        vector<int> cycle;
        cycle.push_back(next + 1);
        while (path.size()) {
          cycle.push_back(path.top() + 1);
          path.pop();
          if (cycle[0] == cycle[cycle.size() - 1]) break;
        }
        cout << cycle.size() << "\n";
        for (int i = cycle.size() - 1; i >= 0; --i) cout << cycle[i] << " ";
        cout << "\n";
        return 0;
      } else if (!done[next]) {
        s.push(next);
      }
    }
    // No neighbors qualify, dead end:
    if (size == s.size()) {
      s.pop();
      inStack[node] = false;
      path.pop();
    }
    done[node] = true;
  }
  cout << "IMPOSSIBLE\n";
  return 0;
}
