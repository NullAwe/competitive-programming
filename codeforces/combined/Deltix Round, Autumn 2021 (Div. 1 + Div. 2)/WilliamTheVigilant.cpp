#include <bits/stdc++.h>
using namespace std;

string str;

bool isABC(int lastInd) {
  return lastInd > 1 && lastInd < str.size() &&
    str[lastInd - 2] == 'a' && str[lastInd - 1] == 'b' && str[lastInd] == 'c';
}

void solve() {
  int n, q; cin >> n >> q;
  cin >> str;
  int abc = 0;
  for (int i = 2; i < n; ++i) if (isABC(i)) ++abc;
  for (int i = 0; i < q; ++i) {
    int ind; cin >> ind; --ind;
    char ch; cin >> ch;
    if (isABC(ind) || isABC(ind + 1) || isABC(ind + 2)) --abc;
    str[ind] = ch;
    if (isABC(ind) || isABC(ind + 1) || isABC(ind + 2)) ++abc;
    // Output:
    cout << abc << endl;
  }
}

int main() {
  solve();
  return 0;
}
