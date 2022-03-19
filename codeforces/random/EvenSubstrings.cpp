#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  string str; cin >> str;
  ll ans = 0;
  for (int i = 0; i < str.size(); ++i) if ((str[i] - '0') % 2 == 0) ans += i + 1;
  cout << ans << '\n';
  return 0;
}
