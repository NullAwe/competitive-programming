#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  vector<ll> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
  vector<ll> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
  if (n == 1) {
    if (a == b) cout << "SMALL\n0\n\n";
    else cout << "IMPOSSIBLE\n";
    return 0;
  }
  if (a == b) {
    cout << "SMALL\n0\n\n";
    return 0;
  }
  vector<ll> tmp = b;
  reverse(tmp.begin(), tmp.end());
  if (tmp == a) {
    cout << "SMALL\n1\nR\n";
    return 0;
  }
  bool end = false;
  sort(tmp.begin(), tmp.end());
  if (tmp != b) {
    reverse(tmp.begin(), tmp.end());
    if (tmp != b) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
    end = true;
  }
  if (n == 2) {
    ll c = 0;
    tmp = b;
    bool sw = a[0] > a[1];
    if (sw) swap(a[0], a[1]);
    while (a != b) {
      if (b[0] > b[1]) swap(b[0], b[1]);
      if (b[0] < a[0] && b[0] < a[1]) {
        cout << "IMPOSSIBLE\n";
        return 0;
      }
      if (b[0] == a[0] && b[1] == a[1]) break;
      if (a[0] == b[0] && a[1] <= b[1] && (b[1] - a[1]) % a[0] == 0) {
        c += (b[1] - a[1]) / a[0];
        break;
      }
      c += b[1] / b[0];
      b[1] -= (b[1] / b[0]) * b[0];
    }
    if (c > 200000) {
      cout << "BIG\n" << c << '\n';
      return 0;
    }
    b = tmp;
    string str;
    while (a != b) {
      if (b[0] > b[1]) {
        swap(b[0], b[1]);
        str += "R";
      }
      if (b[0] == a[0] && b[1] == a[1]) break;
      if (a[0] == b[0] && a[1] <= b[1] && (b[1] - a[1]) % a[0] == 0) {
        for (int i = 0; i < (b[1] - a[1]) / a[0]; ++i) str += "P";
        break;
      }
      for (int i = 0; i < b[1] / b[0]; ++i) str += "P";
      b[1] -= (b[1] / b[0]) * b[0];
    }
    if (sw) str += "R";
    reverse(str.begin(), str.end());
    cout << "SMALL\n" << str.size() << '\n' << str << '\n';
    return 0;
  }
  int cnt = 0;
  string str;
  while (a != b) {
    if (b[0] > b[n - 1]) {
      reverse(b.begin(), b.end());
      str += "R";
      if (a == b) break;
    }
    reverse(b.begin(), b.end());
    if (a == b) {
      str += "R";
      break;
    }
    reverse(b.begin(), b.end());
    for (int i = 1; i < n; ++i) {
      if (b[i] < b[i - 1]) {
        cout << "IMPOSSIBLE\n";
        return 0;
      }
    }
    ll mnA = LLONG_MAX;
    for (int i = 0; i < n; ++i) mnA = min(mnA, a[i]);
    if (mnA > b[0]) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
    while (b[0] <= b[n - 1] && a != b) {
      reverse(b.begin(), b.end());
      if (a == b) {
        str += "R";
        break;
      }
      reverse(b.begin(), b.end());
      str += "P";
      ++cnt;
      bool done = false;
      for (int i = n - 1; i > 0; --i) {
        if (b[i] < b[i - 1]) done = true;
        b[i] -= b[i - 1];
      }
      if (done) break;
    }
  }
  if (cnt > 200000) {
    cout << "BIG\n" << cnt << '\n';
    return 0;
  }
  reverse(str.begin(), str.end());
  cout << "SMALL\n" << str.size() << '\n' << str << '\n';
  return 0;
}
