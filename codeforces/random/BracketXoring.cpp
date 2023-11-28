#include <bits/stdc++.h>
using namespace std;

inline char flip(char c) {
  return (char) ('0' + '1' - c);
}

void solve() {
  int n, cnt = 0; cin >> n;
  string s; cin >> s;
  n *= 2;
  for (int i = 0; i < n; ++i) cnt += s[i] == '1';
  if (s[0] != s.back() || cnt % 2) {
    cout << -1 << '\n';
    return;
  }
  bool oi = (s.back() == '1');
  vector<string> ans;
  bool first = true;
  string t = "";
  for (int i = 0; i + 3 < n; i += 4) {
    cnt = 0;
    for (int j = 0; j < 4; ++j) cnt += s[i + j] == '1';
    if (cnt % 2 == 0) {
      t += "()()";
      continue;
    }
    if (s[i] == s[i + 1]) t += first ? "((()" : "))()";
    else t += first ? "()((" : "()))";
    first = !first;
  }
  if (n % 4) t += s[n - 1] == s[n - 2] ? "()" : "))";
  ans.push_back(t);
  for (int i = 0; i < n; i += 2) {
    if (t[i] != t[i + 1]) s[i] = flip(s[i]), s[i + 1] = flip(s[i + 1]);
    else if (t[i] == '(') s[i] = flip(s[i]);
    else s[i + 1] = flip(s[i + 1]);
  }
  t = "";
  for (int i = 0; i + 3 < n; i += 4) {
    if (s[i] == s[i + 1]) t += "()()";
    else t += "(())";
  }
  if (n % 4) t += "()";
  ans.push_back(t);
  for (int i = 0; i < n; i += 2) {
    if (t[i] != t[i + 1]) s[i] = flip(s[i]), s[i + 1] = flip(s[i + 1]);
    else if (t[i] == '(') s[i] = flip(s[i]);
    else s[i + 1] = flip(s[i + 1]);
  }
  t = "";
  for (int i = 0; i < n; ++i) {
    if (i % 2 == 0) {
      if (i && s[i - 1] != s[0] && s[i] == s[0]) t += ')';
      else t += '(';
    } else {
      if (i < n - 1 && s[i] == s[0] && s[i + 1] != s[0]) t += '(';
      else t += ')';
    }
  }
  ans.push_back(t);
  for (int i = 0; i < n; ++i) {
    if ((i % 2 == 0 && t[i] == '(') || (i % 2 == 1 && t[i] == ')')) s[i] = flip(s[i]);
  }
  first = true;
  t = "";
  for (int i = 0; i < n; ++i) {
    if (i == n - 1) t += ")";
    else if (s[i] != s[i + 1]) t += "(";
    else if (i && s[i] == s[0] && s[i - 1] != s[0]) t += ")";
    else t += "()", ++i;
  }
  ans.push_back(t);
  if (s[0] == '0') {
    t = "";
    for (int i = 0; i < n / 2; ++i) t += "()";
    ans.push_back(t);
  }
  cout << ans.size() << '\n';
  for (string st : ans) cout << st << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
