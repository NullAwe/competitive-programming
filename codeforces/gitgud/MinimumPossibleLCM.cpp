#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX_A = 10000001;

int main() {
  int n; cin >> n;
  vector<int> arr(MAX_A);
  vector<pair<int, int>> m(MAX_A, {-1, -1});
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    ++arr[a];
    if (m[a].first < 0) m[a].first = i;
    else m[a].second = i;
  }
  ll ans = LLONG_MAX;
  int x, y;
  // Finds minimum LCM for a given GCD:
  for (int i = MAX_A - 1; i > 0; --i) {
    vector<int> mults(2);
    int ind = 0;
    for (int j = i; j < MAX_A && ind < 2; j += i) {
      if (arr[j] > 0) mults[ind++] = j;
      if (arr[j] > 1 && ind < 2) mults[ind++] = j;
    }
    if (mults[0] == 0 || mults[1] == 0) continue;
    ll comp = (ll) mults[0] * mults[1] / i;
    if (ans > comp) {
      ans = comp;
      x = m[mults[0]].first;
      y = m[mults[1]].first;
      if (x == y) y = m[mults[1]].second;
    }
  }
  // Guarantees that x < y:
  if (x > y) {
    int tmp = x;
    x = y;
    y = tmp;
  }
  // Output:
  cout << x + 1 << " " << y + 1 << endl;
  return 0;
}
