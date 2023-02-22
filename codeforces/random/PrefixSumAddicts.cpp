#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  vector<int> arr;
  int last = INT_MIN;
  for (int i = 0; i < k; ++i) {
    int x; cin >> x;
    if (last == INT_MIN) {
      long long sum = 0;
      for (int j = 0; j < n - k + 1; ++j) sum += INT_MIN;
      long long diff = x - sum;
      diff = (diff + n - k) / (n - k + 1);
      arr.push_back((int) INT_MIN + diff);
    } else arr.push_back(x - last);
    last = x;
  }
  vector<int> copy = arr;
  sort(copy.begin(), copy.end());
  cout << (copy == arr ? "Yes\n" : "No\n");
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
