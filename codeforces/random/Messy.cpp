#include <bits/stdc++.h>
using namespace std;

void rev(string& str, int l, int r) {
  for (int i = l; i < (l + r + 1) >> 1; ++i) swap(str[i], str[r - i + l]);
}

void solve() {
  int n, k; cin >> n >> k;
  string str; cin >> str;
  int flips = 0;
  vector<pair<int, int>> flipped;
  for (int i = 0; i < n; ++i) {
    if (i < (k - 1) * 2) {
      if (i & 1) {
        if (str[i] == '(') {
          int back = 0;
          for (int j = i; j < n; ++j) {
            if (str[j] == ')') {
              back = j;
              break;
            }
          }
          rev(str, i, back);
          ++flips, flipped.push_back({i + 1, back + 1});
        }
      } else {
        if (str[i] == ')') {
          int back = 0;
          for (int j = i; j < n; ++j) {
            if (str[j] == '(') {
              back = j;
              break;
            }
          }
          rev(str, i, back);
          ++flips, flipped.push_back({i + 1, back + 1});
        }
      }
    } else {
      if (i < n - (n - (k - 1) * 2) / 2) {
        if (str[i] == ')') {
          int back = 0;
          for (int j = i; j < n; ++j) {
            if (str[j] == '(') {
              back = j;
              break;
            }
          }
          rev(str, i, back);
          ++flips, flipped.push_back({i + 1, back + 1});
        }
      } else {
        if (str[i] == '(') {
          int back = 0;
          for (int j = i; j < n; ++j) {
            if (str[j] == ')') {
              back = j;
              break;
            }
          }
          rev(str, i, back);
          ++flips, flipped.push_back({i + 1, back + 1});
        }
      }
    }
  }
  cout << flips << '\n';
  for (pair<int, int> flip : flipped) cout << flip.first << ' ' << flip.second << '\n';
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
