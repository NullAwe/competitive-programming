#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define ppp pair<pii, pii>

const int SZ = 30, MAX_N = 300001;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool use[SZ][2 * MAX_N];
ll ts[SZ][2 * MAX_N];

void init() {
  for (int i = 0; i < SZ; ++i) for (int j = 0; j < MAX_N; ++j) ts[i][j] = 0;
  for (int i = 0; i < SZ; ++i) for (int j = 0; j < 2 * MAX_N; ++j) use[i][j] = (rng() & 1) != 0;
}

int n, q;

void modify(int p, int v) {
  for (int ind = 0; ind < SZ; ++ind) {
    int i = p + n;
    for (ts[ind][i] = use[ind][v]; i > 1; i >>= 1) ts[ind][i >> 1] = ts[ind][i] + ts[ind][i ^ 1];
  }
}

bool query(int l, int r, int k) {
  for (int ind = 0; ind < SZ; ++ind) {
    ll sum = 0;
    int i = l, j = r;
    for (i += n, j += n; i < j; i >>= 1, j >>= 1) {
      if (i & 1) sum += ts[ind][i++];
      if (j & 1) sum += ts[ind][--j];
    }
    if (sum % k) return false;
  }
  return true;
}

void solve() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> q;
  vector<int> nums, arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<ppp> qs(q);
  for (int i = 0; i < q; ++i) {
    int t, a, b; cin >> t >> a >> b;
    qs[i] = {{t, a}, {b, 0}};
    if (t == 2) { int c; cin >> c; qs[i].second.second = c; }
  }
  for (int num : arr) nums.push_back(num);
  for (ppp p : qs) if (p.first.first == 1) nums.push_back(p.second.first);
  sort(nums.begin(), nums.end());
  for (int i = 0; i < n; ++i) arr[i] = lower_bound(nums.begin(), nums.end(), arr[i]) - nums.begin();
  for (int i = 0; i < q; ++i) if (qs[i].first.first == 1) qs[i].second.first = lower_bound(nums.begin(), nums.end(), qs[i].second.first) - nums.begin();
  for (int i = 0; i < n; ++i) modify(i, arr[i]);
  for (int i = 0; i < q; ++i) {
    if (qs[i].first.first == 1) modify(qs[i].first.second - 1, qs[i].second.first);
    else cout << (query(qs[i].first.second - 1, qs[i].second.first, qs[i].second.second) ? "YES\n" : "NO\n");
  }
}

int main() {
  init(), solve();
  return 0;
}
