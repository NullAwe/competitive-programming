#include <bits/stdc++.h>
using namespace std;

// Finds if he can get through his friends or not:
bool works(vector<vector<int>>& adj, int node, int par, vector<int>& fd, vector<int>& pd) {
  int done = 0;
  for (int next : adj[node]) {
    if (next == par) continue;
    ++done;
    if (works(adj, next, node, fd, pd)) return true;
  }
  if (done == 0 && pd[node] < fd[node]) return true;
  return false;
}

void solve() {
  int n, k; cin >> n >> k;
  vector<int> fs(k);
  for (int i = 0; i < k; ++i) {
    cin >> fs[i];
    --fs[i];
  }
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b;
    --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  // Runs BFS on all the friends:
  vector<int> fd(n, -1);
  queue<int> q;
  for (int f : fs) {
    fd[f] = 0;
    q.push(f);
  }
  while (q.size()) {
    int node = q.front(); q.pop();
    for (int next : adj[node]) {
      if (fd[next] < 0) {
        fd[next] = fd[node] + 1;
        q.push(next);
      }
    }
  }
  // Runs BFS on the person:
  vector<int> pd(n, -1);
  queue<int> q2;
  pd[0] = 0;
  q2.push(0);
  while (q2.size()) {
    int node = q2.front(); q2.pop();
    for (int next : adj[node]) {
      if (pd[next] < 0) {
        pd[next] = pd[node] + 1;
        q2.push(next);
      }
    }
  }
  bool yes = works(adj, 0, -1, fd, pd);
  // Output:
  cout << (yes ? "YES" : "NO") << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
