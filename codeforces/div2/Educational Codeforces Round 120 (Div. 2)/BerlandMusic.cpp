#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> rat(n); for (int i = 0; i < n; ++i) cin >> rat[i];
  string str; cin >> str;
  int zero = 0;
  for (int i = 0; i < n; ++i) if (str[i] == '0') ++zero;
  vector<pair<int, int>> zeroes(zero), ones(n - zero);
  int ind0 = 0, ind1 = 0;
  for (int i = 0; i < n; ++i) {
    if (str[i] == '0') zeroes[ind0++] = {rat[i], i};
    else ones[ind1++] = {rat[i], i};
  }
  sort(zeroes.begin(), zeroes.end()); sort(ones.begin(), ones.end());
  int start0 = 1, start1 = zero + 1;
  vector<int> ans(n);
  for (pair<int, int> p : zeroes) ans[p.second] = start0++;
  for (pair<int, int> p : ones) ans[p.second] = start1++;
  // Output:
  for (int num : ans) cout << num << ' ';
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
