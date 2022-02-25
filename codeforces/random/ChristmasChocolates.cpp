#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

const int MAX_NODES = 1e7;

struct customhash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

int main() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  gp_hash_table<int, int, customhash> nums; for (int num : arr) nums[num] = 100;
  set<int> twos; for (int i = 0; i < 31; ++i) twos.insert(1 << i);
  int nodes[MAX_NODES]; for (int i = 0; i < MAX_NODES; ++i) nodes[i] = -1;
  int ind = 0;
  gp_hash_table<int, int, customhash> parent;
  gp_hash_table<int, int, customhash> done;
  queue<int> q; for (int num : arr) q.push(num);
  while (q.size()) {
    int node = q.front(); q.pop();
    if (done[node] == 100) continue;
    done[node] = 100;
    nodes[ind++] = node;
    int next = (*twos.lower_bound(node)) - node;
    parent[node] = next;
    if (next > 0) q.push(next);
  }
  nodes[ind++];
  gp_hash_table<int, vector<int>, customhash> adj;
  for (int i = 0; i < ind; ++i) adj[i] = vector<int>();
  for (int i = 0; i < ind - 1; ++i) {
    adj[nodes[i]].push_back(parent[nodes[i]]);
    adj[parent[nodes[i]]].push_back(nodes[i]);
  }
  int last = 0;
  queue<pair<int, int>> q2; q2.push({0, -1});
  while (q2.size()) {
    pair<int, int> f = q2.front(); q2.pop();
    int node = f.first, p = f.second;
    last = node;
    for (int next : adj[node]) if (next != p) q2.push({next, node});
  }
  int second = last, dist = 0;
  queue<pair<pair<int, int>, int>> q3; q3.push({{last, -1}, 0});
  while (q3.size()) {
    pair<pair<int, int>, int> f = q3.front(); q3.pop();
    int node = f.first.first, p = f.first.second, d = f.second;
    if (nums[node] == 100) second = node, dist = d;
    for (int next : adj[node]) if (next != p) q3.push({{next, node}, d + 1});
  }
  int a, b, c = dist;
  for (int i = 0; i < n; ++i) {
    if (arr[i] == last) a = i + 1;
    if (arr[i] == second) b = i + 1;
  }
  cout << a << ' ' << b << ' ' << c << endl;
}
