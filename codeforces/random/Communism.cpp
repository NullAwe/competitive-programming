#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, a, b; cin >> n >> a >> b;
  string str; cin >> str;
  vector<bool> has(26);
  vector<char> encoded;
  for (int i = 0; i < n; ++i) {
    if (!has[str[i] - 'a']) encoded.push_back(str[i]);
    has[str[i] - 'a'] = true;
  }
  map<char, pair<pair<int, int>, int>> m;
  for (char ch : encoded) {
    int l = -1, r = -1, num = 0;
    for (int i = 0; i < n; ++i) {
      if (str[i] == ch) {
        if (l < 0) l = i;
        r = i;
        ++num;
      }
    }
    m[ch] = {{l, r}, num};
  }
  // Finds answer using bitwise dynamic programming:
  vector<pair<pair<int, int>, pair<int, bool>>> memo(1 << encoded.size());
  memo[0] = {{INT_MAX, INT_MIN}, {0, true}};
  for (int i = 0; i < encoded.size(); ++i) {
    int doing = 1 << i;
    pair<pair<int, int>, int> p = m[encoded[i]];
    bool possible = (ll) p.second * b >= (ll) a * (p.first.second - p.first.first + 1);
    memo[doing] = {{p.first.first, p.first.second}, {p.second, possible}};
  }
  for (int i = 1; i < memo.size(); ++i) {
    for (int j = 1; j < encoded.size(); ++j) {
      int right = i & ((1 << j) - 1), left = i - right;
      int l = min(memo[left].first.first, memo[right].first.first);
      int r = max(memo[left].first.second, memo[right].first.second);
      int total = memo[left].second.first + memo[right].second.first;
      memo[i] = {{l, r}, {total, memo[i].second.second}};
      if ((!memo[left].second.second || !memo[right].second.second)) continue;
      memo[i].second.second = true;
    }
    for (int j = 0; j < encoded.size(); ++j) {
      if (!(i & (1 << j))) continue;
      int last = i ^ (1 << j);
      char cur = encoded[j];
      if (!memo[last].second.second) continue;
      int left = min(m[cur].first.first, memo[last].first.first);
      int right = max(m[cur].first.second, memo[last].first.second);
      int total = m[cur].second + memo[last].second.first;
      memo[i] = {{left, right}, {total, memo[i].second.second}};
      if ((ll) total * b >= (ll) a * (right - left + 1)) memo[i].second.second = true;
    }
  }
  set<char> ans;
  for (int i = 0; i < encoded.size(); ++i)
    if (memo[(memo.size() - 1) ^ (1 << i)].second.second) ans.insert(encoded[i]);
  // Output:
  cout << ans.size() << ' ';
  for (char ch : ans) cout << ch << ' ';
  cout << endl;
  return 0;
}