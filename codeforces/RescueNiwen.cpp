#include <bits/stdc++.h>
using namespace std;

int ceilInd(vector<int>& v, int l, int r, int key) {
  while (r - l > 1) {
    int m = l + (r - l) / 2;
    if (v[m] >= key) r = m;
    else l = m;
  }
  return r;
}

int lis(vector<int>& v, vector<int>& indMap) {
    if (v.size() == 0) return 0;
    vector<int> tail(v.size(), 0);
    int length = 1, tl = n;
    tail[0] = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i] < tail[0]) tail[0] = v[i];
        else if (v[i] > tail[length - 1]) tail[length++] = v[i];
        else tail[CeilIndex(tail, -1, length - 1, v[i])] = v[i];
    }
    return length;
}

void solve() {
  int n; cin >> n;
  string str; cin >> str;
  vector<pair<string, int>> sorted(n);
  for (int i = 0; i < n; ++i) sorted[i] = str.substr(i);
  sort(sorted.begin(), sorted.end());
  vector<int> indMap(n);
  for (int i = 0; i < n; ++i) indMap[sorted[i].second] = i;
  cout << lis(str, indMap) << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
