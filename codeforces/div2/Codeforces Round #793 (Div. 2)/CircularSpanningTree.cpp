#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  string str; cin >> str;
  int sum = 0; for (int i = 0; i < n; ++i) sum += str[i] - '0';
  if ((sum & 1) || !sum) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
  if (sum == n) {
    for (int i = 2; i <= n; ++i) cout << i << ' ' << 1 << '\n';
    return;
  }
  int zero = 0;
  for (int i = 0; i < n; ++i) if (str[i] == '0' && str[(i + n - 1) % n] == '1') { zero = i; break; }
  int lastStart = zero, lastEnd = zero, parity = 0;
  stack<int> todo; todo.push(zero);
  for (int i = zero + 1; i < zero + n; ++i) {
    int ind = i % n, last = (i - 1) % n;
    if (str[ind] == '0') {
      if (str[last] == '0') {
        cout << ind + 1 << ' ' << last + 1 << '\n';
        lastEnd = ind;
        if (parity == 1) todo.pop();
        else parity = 1;
        todo.push(ind);
      } else {
        if (parity & 1) {
          cout << ind + 1 << ' ' << todo.top() + 1 << '\n';
          parity = 0;
        } else {
          if (todo.size() > 1) todo.pop();
          else parity = 1;
          cout << ind + 1 << ' ' << todo.top() + 1 << '\n';
        }
        if (parity == 0) todo.pop();
        todo.push(ind);
        parity = 1;
        lastStart = lastEnd = ind;
      }
    } else {
      if (lastEnd == last) {
        if (todo.top() != last) todo.push(last);
      }
      cout << ind + 1 << ' ' << todo.top() + 1 << '\n';
      if (todo.size() > 1) {
        todo.pop();
        parity = 1;
      } else {
        parity = 1 - parity;
      }
    }
  }
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
