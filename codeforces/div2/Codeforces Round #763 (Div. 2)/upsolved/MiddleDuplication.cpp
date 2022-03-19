#include <bits/stdc++.h>
using namespace std;

string str, order;
vector<pair<int, int>> child;
vector<int> parent;
vector<int> sz;
vector<int> m;
vector<bool> should, did;

int fill(int node) {
  return node < 0 ? 0 : sz[node] = fill(child[node].first) + fill(child[node].second) + 1;
}

inline int sizeOf(int node) {
  return node < 0 ? 0 : sz[node];
}

void trav(int node, int add) {
  if (node < 0) return;
  int pos = add + sizeOf(child[node].first);
  order[pos] = str[node];
  m[node] = pos;
  trav(child[node].first, add);
  trav(child[node].second, pos + 1);
}

int dp(int node, int allow) {
  if (!allow || node < 0) return 0;
  int left = dp(child[node].first, allow - 1);
  if (should[m[node]] || left) {
    did[m[node]] = true;
    return left + dp(child[node].second, allow - left - 1) + 1;
  }
  return 0;
}

int main() {
  int n, k; cin >> n >> k;
  cin >> str;
  child = vector<pair<int, int>>(n);
  parent = vector<int>(n);
  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    child[i] = {a, b};
    if (a >= 0) parent[a] = i;
    if (b >= 0) parent[b] = i;
  }
  sz = vector<int>(n);
  fill(0);
  order = string(n, ' ');
  m = vector<int>(n);
  trav(0, 0);
  should = vector<bool>(n);
  int last = 0;
  for (int i = 1; i < n; ++i) {
    if (order[i] == order[last]) continue;
    for (; last < i; ++last) should[last] = order[i] > order[last];
  }
  did = vector<bool>(n);
  dp(0, k);
  for (int i = 0; i < n; ++i) cout << order[i] << (did[i] ? string(1, order[i]) : "");
  cout << '\n';
  return 0;
}
