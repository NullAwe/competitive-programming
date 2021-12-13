#include <bits/stdc++.h>
using namespace std;

#define pi pair<int, int>

int main() {
  int n, k, d; cin >> n >> k >> d;
  vector<int> ps(k); for (int i = 0; i < k; ++i) cin >> ps[i];
  vector<vector<pi>> adj(n);
  for (int i = 1; i < n; ++i) {
    int a, b; cin >> a >> b;
    --a; --b;
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
  }
  vector<int> trav(n);
  for (int num : ps) trav[num - 1] = num;
  queue<int> q;
  for (int num : ps) q.push(num - 1);
  set<int> deleted;
  while (q.size()) {
    int node = q.front(); q.pop();
    for (pi next : adj[node]) {
      if (!trav[next.first]) {
        trav[next.first] = trav[node];
        q.push(next.first);
      } else if (trav[next.first] != trav[node]) {
        deleted.insert(next.second);
      }
    }
  }
  // Output:
  cout << deleted.size() << endl;
  for (int num : deleted) cout << num << ' ';
  cout << endl;
}
