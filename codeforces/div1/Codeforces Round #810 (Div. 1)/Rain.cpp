#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

vector<ll> t;
vector<pair<ll, int>> tl, tr;

void build(int n, vector<ll>& arr, vector<pii>& col) {
  t.resize(2 * n);
  for (int i = 0; i < n; ++i) t[i + n] = arr[i];
  for (int i = n - 1; i > 0; --i) t[i] = max(t[2 * i], t[2 * i + 1]);
  tl.resize(2 * n), tr.resize(2 * n);
  for (int i = 0; i < n; ++i) {
    tl[i + n] = {arr[i] - col[i].first, col[i].first};
    tr[i + n] = {arr[i] + col[i].first, col[i].first};
  }
  for (int i = n - 1; i > 0; --i) {
    tl[i] = tl[2 * i].first > tl[2 * i + 1].first ? tl[2 * i] : tl[2 * i + 1];
    tr[i] = tr[2 * i].first > tr[2 * i + 1].first ? tr[2 * i] : tr[2 * i + 1];
  }
}

ll query(int n, int l, int r) {
  ll ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = max(ans, t[l++]);
    if (r & 1) ans = max(ans, t[--r]);
  }
  return ans;
}

pair<ll, int> query(vector<pair<ll, int>>& tree, int n, int l, int r) {
  pair<ll, int> ans = {LLONG_MIN, 0};
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) {
      if (tree[l].first > ans.first) ans = tree[l];
      ++l;
    }
    if (r & 1) {
      --r;
      if (tree[r].first > ans.first) ans = tree[r];
    }
  }
  return ans;
}

inline void solve() {
  int n, m; cin >> n >> m;
  vector<pii> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i].first >> arr[i].second;
  vector<pii> real(3 * n);
  for (int i = 0; i < n; ++i) {
    real[3 * i] = {arr[i].first - arr[i].second, 1};
    real[3 * i + 1] = {arr[i].first, -2};
    real[3 * i + 2] = {arr[i].first + arr[i].second, 1};
  }
  sort(real.begin(), real.end());
  vector<pii> col; col.push_back(real[0]);
  for (int i = 1; i < 3 * n; ++i) {
    if (real[i].first == real[i - 1].first) col[col.size() - 1].second += real[i].second;
    else col.push_back(real[i]);
  }
  map<int, int> id; for (int i = 0; i < col.size(); ++i) id[col[i].first] = i;
  vector<ll> heights(col.size());
  ll height = 0, slope = col[0].second;
  for (int i = 1; i < col.size(); ++i) {
    height += slope * (col[i].first - col[i - 1].first);
    heights[i] = height;
    slope += col[i].second;
  }
  build(col.size(), heights, col);
  for (int i = 0; i < n; ++i) {
    int l = arr[i].first - arr[i].second, mid = arr[i].first, r = arr[i].first + arr[i].second;
    int li = id[l], mi = id[mid], ri = id[r];
    if (query(col.size(), 0, li) > m || query(col.size(), ri + 1, col.size()) > m) {
      cout << 0;
      continue;
    }
    pair<ll, int> al = query(tl, col.size(), li, mi + 1), ar = query(tr, col.size(), mi, ri + 1);
    if (al.first + l > m || ar.first - 2 * mid + l > m) cout << 0;
    else cout << 1;
  }
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
