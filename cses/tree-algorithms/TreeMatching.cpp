#include <bits/stdc++.h>
using namespace std;

int dp(int node, bool skip, vector<vector<int>>& adj, vector<int>& memo, vector<int>& memo2) {
  if (!skip && memo[node] >= 0) return memo[node];
  if (skip && memo2[node] >= 0) return memo2[node];
  vector<int> vals = vector<int>(adj[node].size());
  int sum = 0;
  for (int i = 0; i < vals.size(); ++i) {
    vals[i] = dp(adj[node][i], false, adj, memo, memo2);
    sum += vals[i];
  }
  if (skip) {
    memo2[node] = sum;
    return memo2[node];
  }
  if (memo[node] >= 0) return memo[node];
  vector<int> skps = vector<int>(adj[node].size());
  for (int i = 0; i < skps.size(); ++i) skps[i] = dp(adj[node][i], true, adj, memo, memo2);
  memo[node] = sum;
  for (int i = 0; i < vals.size(); ++i) memo[node] = max(memo[node], sum - vals[i] + skps[i] + 1);
  return memo[node];
}

int main() {
  int n;
  cin >> n;
  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a - 1].push_back(b - 1);
    adj[b- 1].push_back(a - 1);
  }
  vector<vector<int>> fixed(n, vector<int>());
  vector<bool> done(n);
  queue<int> q;
  q.push(0);
  while (q.size()) {
    int node = q.front();
    q.pop();
    done[node] = true;
    for (int next : adj[node]) if (!done[next]) {
      fixed[node].push_back(next);
      q.push(next);
    }
  }
  vector<int> memo(n, -1), memo2(n, -1);
  cout << dp(0, false, fixed, memo, memo2);
  return 0;
}

