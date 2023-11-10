#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ll sum = 0;
  for (int num : arr) sum += num;
  if (sum % n > 0) {
    cout << "No\n";
    return;
  }
  int avg = (int) (sum / n);
  vector<int> add, sub;
  int same = 0;
  for (int num : arr) {
    int diff = num - avg;
    if (diff == 0) continue;
    bool can = false;
    for (int s = 0; s < 31; ++s) {
      ll nd = (ll) diff + (1 << s);
      if (nd > INT_MAX) continue;
      if (__builtin_popcount((int) nd) == 1) {
        can = true;
        add.push_back(nd), sub.push_back(1 << s);
      }
    }
    if (!can) {
      cout << "No\n";
      return;
    }
  }
  sort(add.begin(), add.end()), sort(sub.begin(), sub.end());
  if (add == sub) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
