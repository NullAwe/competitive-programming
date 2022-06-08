#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n, m;
  cin >> n >> m;
  vector<int> to(n);
  vector<vector<int>> edge(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    ++to[b];
    edge[a].push_back(b);
  }
  vector<int> order(n);
  int ind = 0;
  queue<int> q;
  for (int i = 0; i < n; ++i) if (to[i] == 0) {
    q.push(i);
    order[ind++] = i + 1;
  }
  while (q.size()) {
    int node = q.front();
    q.pop();
    for (int next : edge[node]) {
      --to[next];
      if (to[next] == 0) {
        q.push(next);
        order[ind++] = next + 1;
      }
    }
  }
  if (ind < n) cout << "IMPOSSIBLE";
  else for (int num : order) cout << num << " ";
  return 0;
}
