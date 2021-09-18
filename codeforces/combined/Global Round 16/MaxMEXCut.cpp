#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string b1, b2; cin >> b1 >> b2;
  int sum = 0;
  bool has[2];
  has[0] = has[1] = false;
  for (int i = 0; i < n; ++i) {
    bool thisHas[2];
    thisHas[0] = thisHas[1] = false;
    thisHas[b1[i] - '0'] = thisHas[b2[i] - '0'] = true;
    if (thisHas[0] && thisHas[1]) {
      sum += 2;
      if (has[0] && !has[1]) ++sum;
      has[0] = has[1] = false;
    } else if (thisHas[0]) {
      if (has[0]) ++sum;
      else if (has[1]) {
        sum += 2;
        has[0] = has[1] = false;
      } else has[0] = true;
    } else if (thisHas[1]) {
      if (has[0]) {
        sum += 2;
        has[0] = has[1] = false;
      } else has[1] = true;
    }
  }
  if (has[0]) ++sum;
  // Output:
  cout << sum << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}