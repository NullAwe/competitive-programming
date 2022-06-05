#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  vector<int> count(n); count[0] = 1;
  int sum = 0;
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    sum = (sum + x) % n;
    sum = (sum + n) % n;
    ans += count[sum];
    ++count[sum];
  }
  cout << ans << '\n';
}

