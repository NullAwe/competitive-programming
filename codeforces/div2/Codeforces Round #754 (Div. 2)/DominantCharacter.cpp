#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string str; cin >> str;
  // Output:
  if (str.find("aa") != string::npos) {
    cout << 2 << endl;
  } else if (str.find("aba") != string::npos || str.find("aca") != string::npos) {
    cout << 3 << endl;
  } else if (str.find("abca") != string::npos || str.find("acba") != string::npos) {
    cout << 4 << endl;
  } else if (str.find("abbacca") != string::npos ||str.find("accabba") != string::npos){
    cout << 7 << endl;
  } else {
    cout << -1 << endl;
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
