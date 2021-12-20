#include <bits/stdc++.h>
using namespace std;

void build(vector<pair<int, pair<int, int>>>& t, int n) {
  for (int i = n - 1; i > 0; --i) {
    t[i].second.first = min(t[i << 1].second.first, t[(i << 1) | 1].second.first);
    t[i].second.second = max(t[i << 1].second.second, t[(i << 1) | 1].second.second);
  }
}

void modify(vector<pair<int, pair<int, int>>>& t, int n, int p, int v) {
  for (t[p += n].first = v; p > 1; p >>= 1) t[p >> 1].first = max(t[p].first, t[p ^ 1].first);
}

int query(vector<pair<int, pair<int, int>>>& t, int n, int v) {
  int ind = 1;
  // Takes care of a special case:
  if (n == 1 && t[1].first < v) return -1;
  while (ind < n) {
    if (t[ind].first < v) return -1;
    if (t[ind << 1].second.first < t[(ind << 1) | 1].second.first) {
      if (t[ind << 1].first >= v) ind <<= 1;
      else ind = (ind << 1) | 1;
    } else {
      if (t[(ind << 1) | 1].first >= v) ind = (ind << 1) | 1;
      else ind <<= 1;
    }
  }
  return ind - n;
}

int main() {
  int n, m; cin >> n >> m;
  int size = 1; while (size < 2 * n) size <<= 1;
  vector<pair<int, pair<int, int>>> t(size);
  for (int i = 0; i < size / 2; ++i) t[i + size / 2] = {0, {i, i}};
  build(t, size / 2);
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    modify(t, size / 2, i, a);
  }
  for (int i = 0; i < m; ++i) {
    int a; cin >> a;
    int ind = query(t, size / 2, a);
    if (ind >= 0) modify(t, size / 2, ind, t[ind + size / 2].first - a);
    // Output:
    cout << ind + 1 << ' ';
  }
  // Output:
  cout << endl;
  return 0;
}
