#include <bits/stdc++.h>
using namespace std;

#define ll long long

const vector<string> p = {
  "ANOT", "ANTO", "AONT", "AOTN", "ATNO", "ATON",
  "NAOT", "NATO", "NOAT", "NOTA", "NTAO", "NTOA",
  "OANT", "OATN", "ONAT", "ONTA", "OTAN", "OTNA",
  "TANO", "TAON", "TNAO", "TNOA", "TOAN", "TONA"
};

void modify(vector<int>& t, int n, int p, int value) {
  for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

int query(vector<int>& t, int n, int l, int r) {
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res += t[l++];
    if (r & 1) res += t[--r];
  }
  return res;
}

ll getMoves(map<char, vector<int>>& m, string& s) {
  int n = s.size();
  vector<int> t(2 * n, 0);
  map<char, int> inds;
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += query(t, n, m[s[i]][inds[s[i]]], n);
    modify(t, n, m[s[i]][inds[s[i]]], 1);
    ++inds[s[i]];
  }
  return ans;
}

void solve() {
  string str; cin >> str;
  map<char, vector<int>> m;
  for (int i = 0; i < str.size(); ++i) m[str[i]].push_back(i);
  map<char, int> count;
  for (int i = 0; i < str.size(); ++i) ++count[str[i]];
  ll moves = 0;
  string ans = "";
  // Checks each permutation of letter orders:
  for (string perm : p) {
    string s = "";
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < count[perm[i]]; ++j)
        s += perm[i];
    ll tm = getMoves(m, s);
    // Updates the answer:
    if (tm >= moves) {
      moves = tm;
      ans = s;
    }
  }
  // Output:
  cout << ans << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}

