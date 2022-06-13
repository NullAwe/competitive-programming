#include <bits/stdc++.h>
using namespace std;

char q1(int x) {
  printf("? 1 %d\n", x); fflush(stdout);
  char res; scanf(" %c", &res);
  return res;
}

int q2(int x, int y) {
  if (x > y) return 0;
  printf("? 2 %d %d\n", x, y); fflush(stdout);
  int res; scanf("%d", &res);
  return res;
}

void solve() {
  int n; cin >> n;
  vector<int> ans(n), last(26, -1); ans[0] = 1;
  vector<char> chs(n); chs[0] = q1(1); last[chs[0] - 'a'] = 0;
  for (int i = 1; i < n; ++i) {
    ans[i] = q2(1, i + 1);
    if (ans[i] > ans[i - 1]) {
      chs[i] = q1(i + 1); last[chs[i] - 'a'] = i;
      continue;
    }
    vector<int> bs;
    for (int i = 0; i < 26; ++i) if (last[i] >= 0) bs.push_back(last[i]);
    sort(bs.begin(), bs.end());
    int lo = -1, hi = bs.size();
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (q2(bs[mid] + 2, i + 1) == bs.size() - mid - 1) lo = mid;
      else hi = mid;
    }
    chs[i] = chs[bs[hi]]; last[chs[i] - 'a'] = i;
  }
  cout << "! ";
  for (int i = 0; i < n; ++i) cout << chs[i];
  cout << '\n'; fflush(stdout);
}

int main() {
  solve();
  return 0;
}