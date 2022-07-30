#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  string str; cin >> str;
  vector<int> p0(n + 1), p1(n + 1);
  for (int i = 1; i < n; ++i)
    p0[i + 1] = p0[i] + (str[i] == '0' && str[i - 1] == '0'),
      p1[i + 1] = p1[i] + (str[i] == '1' && str[i - 1] == '1');
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b;
    int n0 = p0[b] - p0[a], n1 = p1[b] - p1[a];
    if (str[a - 1] == '0') ++n0;
    else ++n1;
    cout << max(n0 + (str[a - 1] == '1'), n1 + (str[a - 1] == '0')) << '\n';
  }
  return 0;
}
