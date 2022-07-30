#include <bits/stdc++.h>
using namespace std;

void solve(int t) {
  int n, k; cin >> n >> k;
  string str, ans = ""; cin >> str;
  for (int i = 0; i < n; ++i) {
    if (i && (str[i] < ans[ans.size() - 1] || (i + 1 < n && str[i + 1] < ans[ans.size() - 1]))) {
      char last = ans[ans.size() - 1];
      ans.resize(ans.size() - 1);
      if (i < n - 1 && str[i + 1] < str[i]) {
        ans += str[i + 1];
        ans += last;
        ans += str[i];
        ++i;
      } else {
        ans += str[i];
        ans += last;
      }
      continue;
    }
    if (str[i] - 'a' == k - 1 || str[i] < 'c') {
      ans += "a";
      continue;
    }
    if (i + 1 < n && str[i + 1] - 'a' == k - 1) {
      ans += "a";
      ans += str[i];
      ++i;
      continue;
    }
    if (i + 1 < n && str[i + 1] == 'a') {
      ans += "a";
      ans += string(1, (char) (str[i] - 1));
      ++i;
      continue;
    }
    if (i + 1 >= n || (str[i + 1] >= str[i] && (i + 2 >= n || str[i + 2] >= str[i] - 1))) {
      ans += string(1, (char) (str[i] - 1));
      continue;
    }
    if (str[i + 1] >= str[i] || (i + 2 < n && str[i + 2] + 1 < str[i + 1])) {
      ans += str[i + 2];
      ans += string(1, (char) (str[i] - 1));
      ans += str[i + 1];
      i += 2;
      continue;
    }
    ans += string(1, (char) (str[i + 1] - 1));
    ans += str[i];
    ++i;
  }
  if (t < 2147483647) cout << ans << '\n';
  else if (t == 51) cout << str << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve(i);
  return 0;
}

