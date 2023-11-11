#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

string ans = "";

inline int msb(int x) {
  int m = 0;
  while (x) ++m, x >>= 1;
  return m;
}

void solve(int n, vector<pii> arr) {
  if (n == 0) return;
  vector<int> msbs(n);
  vector<int> cnt(32);
  for (int i = 0; i < n; ++i) ++cnt[msbs[i] = msb(arr[i].first)];
  vector<pii> smp;
  bool started = false;
  int cur = -1, lab = 0;
  vector<pii> curr;
  for (int i = 0; i < n; ++i) {
    if (msbs[i] != cur) {
      cur = msbs[i], lab = 0;
      solve(curr.size(), curr);
      curr.clear();
    }
    if (cnt[msbs[i]] > 2) {
      started = true;
      curr.push_back({arr[i].first - (1 << (msb(arr[i].first) - 1)), arr[i].second});
    } else if (started) {
      ans[arr[i].second] = (char) (lab + '0');
      ++lab;
    } else {
      smp.push_back(arr[i]);
    }
  }
  solve(curr.size(), curr);
  if (smp.size() == 0) return;
  if (smp.size() == 1) {
    ans[smp[0].second] = '0';
    return;
  }
  if (smp.size() == 2) {
    ans[smp[0].second] = '0';
    ans[smp[1].second] = '1';
    return;
  }
  if (smp.size() == 3) {
    ans[smp[0].second] = '0';
    int a = smp[1].first ^ smp[2].first;
    int b = smp[0].first ^ smp[1].first;
    int c = smp[0].first ^ smp[2].first;
    if (a >= b && a >= c) ans[smp[1].second] = ans[smp[2].second] = '1';
    else if (c >= b && c >= a) ans[smp[2].second] = '0', ans[smp[1].second] = '1';
    else ans[smp[1].second] = '0', ans[smp[2].second] = '1';
    return;
  }
  string bst = "0000";
  int mn = -1;
  for (int i = 0; i < 3; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      int n1 = i ? 0 : (j > 1 ? 1 : 2);
      int n2 = j < 3 ? 3 : (i < 2 ? 2 : 1);
      int val = min(smp[i].first ^ smp[j].first, smp[n1].first ^ smp[n2].first);
      if (val > mn) {
        bst = "0000";
        bst[i] = bst[j] = '1';
        mn = val;
      }
    }
  }
  for (int i = 0; i < 4; ++i) {
    ans[smp[i].second] = bst[i];
  }
  for (int i = 4; i < (int) smp.size(); ++i) {
    ans[smp[i].second] = (char) ('0' + '1' - ans[smp[i - 1].second]);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<pii> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i].first;
    arr[i].second = i, ans += "x";
  }
  sort(arr.begin(), arr.end());
  solve(n, arr);
  cout << ans << '\n';
}