#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  int pos = -1;
  for (int i = 0; i < n; ++i) if (arr[i] > 0) pos = i;
  if (pos < 0) {
    cout << n - 1 << '\n';
    for (int i = n - 1; i > 0; --i) cout << i << ' ' << i + 1 << '\n';
    return;
  }
  int times = 0;
  while (arr[pos] < 20) arr[pos] <<= 1, ++times;
  vector<int> idx;
  for (int i = 0; i < n; ++i) if (arr[i] < 0) arr[i] += arr[pos], idx.push_back(i + 1);
  cout << n - 1 + times + idx.size() << '\n';
  for (int i = 0; i < times; ++i) cout << pos + 1 << ' ' << pos + 1 << '\n';
  for (int num : idx) cout << num << ' ' << pos + 1 << '\n';
  for (int i = 1; i < n; ++i) cout << i + 1 << ' ' << i << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}