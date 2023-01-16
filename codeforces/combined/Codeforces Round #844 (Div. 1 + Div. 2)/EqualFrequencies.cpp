#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

inline void solve() {
  int n; cin >> n;
  vector<int> check;
  for (int i = 1; i <= n; ++i) if (n % i == 0 && n / i <= 26) check.push_back(i);
  string str; cin >> str;
  vector<int> count(26);
  for (int i = 0; i < n; ++i) ++count[str[i] - 'a'];
  int mn = INT_MAX;
  vector<int> store;
  for (int num : check) {
    int chars = n / num;
    vector<int> c2(26);
    for (int i = 0; i < 26; ++i) if (count[i] >= num) c2[i] = num, --chars;
    vector<pii> arr;
    for (int i = 0; i < 26; ++i) if (count[i] && count[i] < num) arr.push_back({count[i], i});
    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());
    for (pii p : arr) if (chars) c2[p.second] = num, --chars;
    for (int i = 0; i < 26; ++i) if (!count[i] && chars) c2[i] = num, --chars;
    int diff = 0;
    for (int i = 0; i < 26; ++i) diff += abs(count[i] - c2[i]);
    if (diff < mn) mn = diff, store = c2;
  }
  cout << mn / 2 << '\n';
  for (int i = 0; i < n; ++i) {
    int val = str[i] - 'a';
    if (store[val] >= count[val] && store[val]) {
       --store[val], --count[val];
       continue;
    }
    for (int j = 0; j < 26; ++j) {
      if (store[j] > count[j]) {
        str[i] = (char) (j + 'a');
        --count[val], --store[j];
        break;
      }
    }
  }
  cout << str << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
