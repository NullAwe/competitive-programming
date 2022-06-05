#include <iostream>
#include <vector>
using namespace std;

void modify(vector<int>& t, int n, int p, int v) {
  for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

int query(vector<int>& t, int n, int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

int main() {
  int n, k; cin >> n >> k;
  vector<int> t(2 * n);
  for (int i = 0; i < n; ++i) modify(t, n, i, 1);
  int size = n, ind = 0;
  for (int i = 0; i < n; ++i) {
    int next = (ind + k) % size;
    int lo = 0, hi = n;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (query(t, n, 0, mid) <= next) lo = mid;
      else hi = mid;
    }
    cout << lo + 1 << ' ';
    modify(t, n, lo, 0);
    --size;
    ind = next;
  }
  cout << '\n';
  return 0;
}
