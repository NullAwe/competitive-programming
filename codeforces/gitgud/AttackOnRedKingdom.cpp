#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<vector<int>> grundy(100, vector<int>(3));
int r = 1;

void rep() {
  for (int i = 90; i >= 0; --i) {
    bool can = true;
    for (int si = 0; si < 5; ++si)
      for (int j = 0; j < 3; ++j) if (grundy[i + si][j] != grundy[95 + si][j]) can = false;
    if (can) {
      r = 95 - i;
      return;
    }
  }
}

int mex(vector<int>& arr) {
  sort(arr.begin(), arr.end());
  if (arr[0]) return 0;
  for (int i = 1; i < arr.size(); ++i) if (arr[i] > arr[i - 1] + 1) return arr[i - 1] + 1;
  return arr[arr.size() - 1] + 1;
}

ll getInd(ll orig) {
  return orig < 100 ? orig : (orig - 100 + r) % r + 100 - r;
}

void solve() {
  vector<int> moves(3);
  int n; cin >> n >> moves[0] >> moves[1] >> moves[2];
  for (int iter = 1; iter < 100; ++iter) {
    vector<int> vals(3);
    vector<int> a, b, c;
    for (int i = 0; i < 3; ++i) a.push_back(grundy[max(iter - moves[i], 0)][i]);
    for (int i = 0; i < 2; ++i) b.push_back(grundy[max(iter - moves[2 * i], 0)][2 * i]);
    for (int i = 0; i < 2; ++i) c.push_back(grundy[max(iter - moves[i], 0)][i]);
    grundy[iter][0] = mex(a), grundy[iter][1] = mex(b), grundy[iter][2] = mex(c);
  }
  rep();
  vector<ll> arr(n);
  int _xor = 0, ans = 0;
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
    _xor ^= grundy[getInd(arr[i])][0];
  }
  for (int i = 0; i < n; ++i) {
    vector<int> tries(3);
    for (int j = 0; j < 3; ++j) tries[j] = grundy[getInd(max(arr[i] - moves[j], 0LL))][j];
    for (int j = 0; j < 3; ++j) if (!(_xor ^ grundy[getInd(arr[i])][0] ^ tries[j])) ++ans;
  }
  cout << ans << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
