#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> ps;

int find(int start, int last, int bit) {
  if (bit == 19) return ((last - start) >> 1) << 1;
  map<int, int> m;
  int ans = 0;
  for (int i = start; i <= last; i += 2) {
    int num = 0;
    for (int b = bit + 1; b < ps.size(); ++b) if (ps[b][i]) num |= (1 << b);
    if (m[num]) ans = max(ans, i + 1 - m[num]);
    else m[num] = i + 1;
  }
  map<int, int> m2;
  for (int i = start + 1; i <= last; i += 2) {
    int num = 0;
    for (int b = bit + 1; b < ps.size(); ++b) if (ps[b][i]) num |= (1 << b);
    if (m2[num]) ans = max(ans, i + 1 - m2[num]);
    else m2[num] = i + 1;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  ps = vector<vector<int>>(20, vector<int>(n + 1));
  for (int i = 0; i < 20; ++i) for (int j = 0; j < n; ++j)
    ps[i][j + 1] = (ps[i][j] + ((arr[j] >> i) & 1)) & 1;
  int ans = 0;
  for (int i = 19; i >= 0; --i) {
    int last = 0, start = -1;
    for (int j = 0; j < n; ++j) {
      int bit = (arr[j] >> i) & 1;
      if (last == 0 && bit == 1) start = j;
      else if (last == 1 && bit == 0) ans = max(ans, find(start, j, i));
      last = bit;
    }
    if (last == 1) ans = max(ans, find(start, n, i));
  }
  cout << ans << '\n';
  return 0;
}
