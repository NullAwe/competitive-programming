#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX_N = 300000;

ll arr[MAX_N];
vector<int> adj[MAX_N];

int parents[MAX_N];
ll maxCC[MAX_N];
bool vis[MAX_N];

ll S = LLONG_MIN, N = 0;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  for (int i = 0; i < MAX_N; ++i) {
    arr[i] = 0;
    vector<int> v; adj[i] = v;
    parents[i] = -1;
    maxCC[i] = LLONG_MIN;
    vis[i] = false;
  }
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> arr[i];
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  // Finds S:
  vector<int> order(n); int ind = 0;
  queue<int> q; q.push(0);
  while (q.size()) {
    int node = q.front(); q.pop(); order[ind++] = node; vis[node] = true;
    for (int next : adj[node]) if (!vis[next]) { q.push(next); parents[next] = node; }
  }
  for (int i = 0; i < MAX_N; ++i) vis[i] = false;
  reverse(order.begin(), order.end());
  for (int node : order) {
    vis[node] = true;
    maxCC[node] = arr[node];
    for (int next : adj[node]) if (vis[next] && maxCC[next] > 0) maxCC[node] += maxCC[next];
  }
  for (ll num : maxCC) S = max(S, num);
  // Finds N:
  for (int i = 0; i < MAX_N; ++i) vis[i] = false;
  for (int node : order) {
    if (vis[node]) continue;
    vis[node] = true;
    if (maxCC[node] != S) continue;
    ++N;
    while (node >= 0 && maxCC[node] > 0) {
      vis[node] = true;
      node = parents[node];
    }
  }
  // Output:
  cout << S * N << ' ' << N << endl;
  return 0;
}
