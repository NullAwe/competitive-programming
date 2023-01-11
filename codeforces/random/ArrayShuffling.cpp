#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  if (n == 1) {
    cout << arr[0] << '\n';
    return;
  }
  for (int i = 0; i < n; ++i) --arr[i];
  vector<pii> real(n);
  for (int i = 0; i < n; ++i) real[i] = {arr[i], i};
  sort(real.begin(), real.end());
  vector<int> count(n);
  for (int num : arr) ++count[num];
  sort(count.begin(), count.end());
  int shift = count[n - 2];
  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    int actual = (i + shift) % n;
    b[real[i].second] = real[actual].first;
  }
  for (int num : b) cout << num + 1 << ' ';
  cout << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}