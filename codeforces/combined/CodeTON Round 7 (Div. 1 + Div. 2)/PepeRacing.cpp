#include <bits/stdc++.h>
using namespace std;

int qry(set<int>& arr) {
  cout << "?";
  for (int num : arr) cout << ' ' << num + 1;
  cout << endl;
  int x; cin >> x;
  return x - 1;
}

inline void solve() {
  int n; cin >> n;
  vector<set<int>> groups(n);
  set<int> avail;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      groups[i].insert(i * n + j);
      avail.insert(i * n + j);
    }
  }
  set<int> fast;
  vector<int> rs(n * n);
  for (int i = 0; i < n; ++i) {
    int num = qry(groups[i]);
    fast.insert(num);
    groups[i].erase(num);
    avail.erase(num);
    rs[num] = i;
  }
  vector<int> order;
  set<int> random;
  int row = 0;
  for (int i = 0; i < n * n - n + 1; ++i) {
    if (avail.empty()) {
      int fastest = -1;
      for (int num : fast) if (!random.count(num)) fastest = num;
      order.push_back(fastest);
      break;
    }
    int fastest = qry(fast);
    row = rs[fastest];
    order.push_back(fastest);
    fast.erase(fastest);
    for (int num : avail) {
      if (groups[row].size() == n) break;
      groups[row].insert(num);
    }
    int nf;
    if (groups[row].size() == n) {
      nf = qry(groups[row]);
      rs[nf] = row;
    } else {
      nf = *avail.begin();
      random.insert(nf);
    }
    fast.insert(nf);
    avail.erase(nf);
    for (int j = 0; j < n; ++j) groups[j].erase(nf);
  }
  cout << "!";
  for (int num : order) cout << ' ' << num + 1;
  cout << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
