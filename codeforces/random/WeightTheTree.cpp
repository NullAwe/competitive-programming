#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;

bool better(pair<int, int> a, pair<int, int> b) {
  return a.first > b.first || (a.first == b.first && a.second < b.second);
}

void dp(int node, int parent, bool can, vector<vector<pair<int, int>>>& memo) {
  if (memo[node][can].first != -1) return;
  memo[node][can] = {0, 0};
  for (int next : adj[node]) {
    if (next == parent) continue;
    dp(next, node, true, memo);
    memo[node][can].first += memo[next][1].first, memo[node][can].second += memo[next][1].second;
  }
  if (can) {
    pair<int, int> comp = {1, adj[node].size()};
    for (int next : adj[node]) {
      if (next == parent) continue;
      dp(next, node, false, memo);
      comp.first += memo[next][0].first, comp.second += memo[next][0].second;
    }
    if (better(comp, memo[node][can])) memo[node][can] = comp;
  }
}

void inflate(int node, int parent, bool can, vector<vector<pair<int, int>>>& memo, vector<bool>& selected) {
  selected[node] = can && memo[node][0] != memo[node][1];
  for (int next : adj[node]) if (next != parent) inflate(next, node, !selected[node], memo, selected);
}

int main() {
  int n; cin >> n;
  if (n == 2) {
    cout << "2 2\n1 1\n";
    return 0;
  }
  adj = vector<vector<int>>(n);
  for (int i = 1; i < n; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<vector<pair<int, int>>> memo(n, vector<pair<int, int>>(2, {-1, -1}));
  dp(0, -1, true, memo); dp(0, -1, false, memo);
  vector<bool> selected(n);
  inflate(0, -1, true, memo, selected);
  cout << memo[0][1].first << ' ' << memo[0][1].second + n - memo[0][1].first << '\n';
  for (int i = 0; i < n; ++i) cout << (selected[i] ? adj[i].size() : 1) << ' ';
  cout << '\n';
  return 0;
}
