#include <bits/stdc++.h>
using namespace std;
 
vector<int> disjoint, rank_;
 
int find(int node) {
  if (disjoint[node] != node) disjoint[node] = find(disjoint[node]);
  return disjoint[node];
}
 
bool join(int x, int y) {
  int xr = find(x), yr = find(y);
  if (xr == yr) return false;
  if (rank_[xr] < rank_[yr]) {
    disjoint[xr] = yr;
    rank_[yr] += rank_[xr];
  } else {
    disjoint[yr] = xr;
    rank_[xr] += rank_[yr];
  }
  return true;
}
 
int main() {
  int n, q;
  cin >> n >> q;
  vector<int> d(n), s(n, 1);
  for (int i = 0; i < n; ++i) d[i] = i;
  disjoint = d;
  rank_ = s;
  int g = n, m = 1;
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    if (join(a - 1, b - 1)) --g;
    m = max(m, max(rank_[find(a - 1)], rank_[find(b - 1)]));
    cout << g << " " << m << "\n";
  }
  return 0;
}
