#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int mn = 0, mx = 0;
  for (int i = 0; i < n; ++i) mn = min(mn, arr[i]), mx = max(mx, arr[i]);
  if (mn == mx) {
    cout << 0 << '\n';
    return;
  }
  if (mx == 0) {
    cout << n - 1 << '\n';
    for (int i = n - 1; i > 0; --i) cout << i << ' ' << i + 1 << '\n';
    return;
  }
  if (mn == 0) {
    cout << n - 1 << '\n';
    for (int i = 1; i < n; ++i) cout << i + 1 << ' ' << i << '\n';
    return;
  }
  int cntN = 0, cntP = 0;
  for (int num : arr) {
    if (num < 0) ++cntN;
    else if (num > 0) ++cntP;
  }
  if (abs(mn) >= abs(mx) && n - 1 + cntP <= 31) {
    int idx = -1;
    for (int i = 0; i < n; ++i) if (arr[i] == mn) idx = i;
    cout << n - 1 + cntP << '\n';
    for (int i = 0; i < n; ++i) {
      if (arr[i] > 0) {
        cout << i + 1 << ' ' << idx + 1 << '\n';
        arr[i] += arr[idx];
      }
    }
    for (int i = n - 1; i > 0; --i) cout << i << ' ' << i + 1 << '\n';
    return;
  }
  if (abs(mn) <= abs(mx) && n - 1 + cntN <= 31) {
    int idx = -1;
    for (int i = 0; i < n; ++i) if (arr[i] == mx) idx = i;
    cout << n - 1 + cntN << '\n';
    for (int i = 0; i < n; ++i) {
      if (arr[i] < 0) {
        cout << i + 1 << ' ' << idx + 1 << '\n';
        arr[i] += arr[idx];
      }
    }
    for (int i = 1; i < n; ++i) cout << i + 1 << ' ' << i << '\n';
    return;
  }
  int pos = -1;
  if (cntP >= cntN) {
    for (int i = 0; i < n; ++i) if (arr[i] > 0) pos = i;
  } else {
    for (int i = 0; i < n; ++i) if (arr[i] < 0) pos = i;
  }
  int times = 0;
  while (abs(arr[pos]) < 20) arr[pos] += arr[pos], ++times;
  vector<int> idx;
  for (int i = 0; i < n; ++i) if (arr[i] != 0 && ((arr[i] < 0) != (arr[pos] < 0))) arr[i] += arr[pos], idx.push_back(i + 1);
  cout << n - 1 + times + (int) idx.size() << '\n';
  for (int i = 0; i < times; ++i) cout << pos + 1 << ' ' << pos + 1 << '\n';
  for (int num : idx) cout << num << ' ' << pos + 1 << '\n';
  if (arr[pos] > 0) for (int i = 1; i < n; ++i) cout << i + 1 << ' ' << i << '\n';
  else for (int i = n - 1; i > 0; --i) cout << i << ' ' << i + 1 << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
