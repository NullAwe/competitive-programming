#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>

const int MOD = 1e9 + 7;

int main() {
  int n, m; cin >> n >> m;
  vector<vector<pli>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a, b, w; cin >> a >> b >> w; --a, --b;
    adj[a].push_back({w, b});
  }
  vector<ll> d(n, -1); d[0] = 0;
  set<pli> s; s.insert({0, 0});
  while (s.size()) {
    pli f = *s.begin(); s.erase(s.begin());
    int node = f.second; ll dist = f.first;
    for (pli p : adj[node]) {
      int next = p.second, w = p.first;
      if (d[next] >= 0 && d[next] <= dist + w) continue;
      s.erase({d[next], next});
      d[next] = dist + w;
      s.insert({d[next], next});
    }
  }
  cout << d[n - 1] << ' ';
  vector<pli> d1(n, {-1, 0}); d1[0] = {0, 1};
  s.insert({0, 0});
  while (s.size()) {
    pli f = *s.begin(); s.erase(s.begin());
    int node = f.second; ll dist = f.first;
    for (pli p : adj[node]) {
      int next = p.second, w = p.first;
      if (d1[next].first == dist + w) d1[next].second = (d1[next].second + d1[node].second) % MOD;
      if (d1[next].first >= 0 && d1[next].first <= dist + w) continue;
      s.erase({d1[next].first, next});
      d1[next] = {dist + w, d1[node].second};
      s.insert({d1[next].first, next});
    }
  }
  cout << d1[n - 1].second << ' ';
  vector<pli> d2(n, {-1, 0}); d2[0] = {0, 0};
  s.insert({0, 0});
  while (s.size()) {
    pli f = *s.begin(); s.erase(s.begin());
    int node = f.second; ll dist = f.first;
    for (pli p : adj[node]) {
      int next = p.second, w = p.first;
      if (d2[next].first >= 0 && (d2[next].first < dist + w ||
          (d2[next].first == dist + w && d2[next].second <= d2[node].second + 1))) continue;
      s.erase({d2[next].first, next});
      d2[next] = {dist + w, d2[node].second + 1};
      s.insert({d2[next].first, next});
    }
  }
  cout << d2[n - 1].second << ' ';
  vector<pli> d3(n, {-1, 0}); d3[0] = {0, 0};
  s.insert({0, 0});
  while (s.size()) {
    pli f = *s.begin(); s.erase(s.begin());
    int node = f.second; ll dist = f.first;
    for (pli p : adj[node]) {
      int next = p.second, w = p.first;
      if (d3[next].first >= 0 && (d3[next].first < dist + w ||
          (d3[next].first == dist + w && d3[next].second >= d3[node].second + 1))) continue;
      s.erase({d3[next].first, next});
      d3[next] = {dist + w, d3[node].second + 1};
      s.insert({d3[next].first, next});
    }
  }
  cout << d3[n - 1].second << '\n';
  return 0;
}
