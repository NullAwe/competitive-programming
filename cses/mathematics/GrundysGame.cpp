#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5000;

vector<int> ans(MAX_N);

int mex(vector<bool> has) {
  for (int i = 0; i < has.size(); ++i) if (!has[i]) return i;
  return has.size();
}

void solve() {
  int n; cin >> n;
  cout << (n >= MAX_N || ans[n] ? "first" : "second") << '\n';
}

int main() {
  for (int i = 3; i < MAX_N; ++i) {
    vector<bool> has(MAX_N / 5);
    for (int j = 1; j <= (i - 1) / 2; ++j) has[ans[j] ^ ans[i - j]] = 1;
    ans[i] = mex(has);
  }
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

