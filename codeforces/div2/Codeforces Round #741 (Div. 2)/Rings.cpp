#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string str; cin >> str;
  int zeroInd = -1;
  for (int i = 0; i < n; ++i) {
    if (str[i] == '0') {
      zeroInd = i;
      break;
    }
  }
  int len = n / 2;
  // Output:
  if (zeroInd < 0) cout << "1 " << (len * 2) << " 1 " << len << endl;
  else if (zeroInd < len) cout << (zeroInd + 1) << " " << n << " " << (zeroInd + 2) << " " << n << endl;
  else cout << "1 " << (zeroInd + 1) << " 1 " << zeroInd << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
