#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> t;
int n, m;
set<pii> trains;

void modify(int p, int v) { for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]); }

int query(int l, int r) {
  int ans = INT_MAX;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = min(ans, t[l++]);
    if (r & 1) ans = min(ans, t[--r]);
  }
  return ans;
}

void solve() {
  cin >> n >> m; t.resize(2 * n);
  for (int i = 0; i < n; ++i) { int x; cin >> x; modify(i, x); }
  int start = 0;
  for (int i = 1; i < n; ++i)
    if (t[i + n] < t[start + n]) trains.insert({start, i - 1}), start = i;
  trains.insert({start, n - 1});
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a;
    int ns = t[a + n] - b;
    pii rng = *--trains.upper_bound({a, INT_MAX});
    if (ns < t[rng.first + n]) {
      int lo = a, hi = n;
      while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (query(a + 1, mid + 1) >= ns) lo = mid;
        else hi = mid;
      }
      if (rng.first < a) trains.insert({rng.first, a - 1});
      trains.erase(rng);
      auto it = trains.upper_bound({a, INT_MAX});
      while (it != trains.end() && it->second <= lo) trains.erase(it), it = trains.upper_bound({a, INT_MAX});
      if (it != trains.end() && it->first <= lo) {
        trains.insert({lo + 1, it->second});
        trains.erase(it);
      }
      trains.insert({a, lo});
    }
    modify(a, t[a + n] - b);
    cout << trains.size() << ' ';
  }
  cout << '\n';
  trains.clear();
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

