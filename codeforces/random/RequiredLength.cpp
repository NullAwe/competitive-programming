#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
  int n; cin >> n;
  ll target = 1; for (int i = 1; i < n; ++i) target *= 10;
  ll x; cin >> x;
  map<ll, int> m; m[x] = 1;
  queue<ll> q; q.push(x);
  while (q.size()) {
    ll node = q.front(), dist = m[node]; q.pop();
    if (node >= target) {
      cout << m[node] - 1 << '\n';
      return;
    }
    ll temp = node;
    while (temp) {
      int digit = temp % 10; temp /= 10;
      if (digit > 1 && !m[node * digit]) m[node * digit] = dist + 1, q.push(node * digit);
    }
  }
  cout << -1 << '\n';
}

int main() {
  solve();
  return 0;
}
