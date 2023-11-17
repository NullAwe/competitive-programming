#include <bits/stdc++.h>
using namespace std;

set<int> in;

bool qry(int v, int k) {
  cout << "? " << v + 1 << ' ' << k << ' ' << in.size();
  for (int num : in) cout << ' ' << num + 1;
  cout << endl;
  bool res; cin >> res;
  return res;
}

bool qry(int v, int k, vector<int>& arr) {
  cout << "? " << v + 1 << ' ' << k << ' ' << arr.size();
  for (int num : arr) cout << ' ' << num + 1;
  cout << endl;
  bool res; cin >> res;
  return res;
}

int find(int n, int v, int k) {
  vector<int> search;
  for (int i = 0; i < n; ++i) search.push_back(i);
  n = search.size();
  int l = 0, r = n - 1;
  while (l != r) {
    int m = (l + r) / 2;
    vector<int> arr(m - l + 1);
    for (int i = 0; i < m - l + 1; ++i) arr[i] = search[i + l];
    if (qry(v, k, arr)) r = m;
    else l = m + 1;
  }
  return l;
}

int main() {
  int big = 1000000000;
  int n; cin >> n;
  int cur = find(n, 0, big);
  in.insert(cur);
  in.insert(find(n, 0, big - 1));
  bool wrap = false;
  for (int i = 0; i < 124; ++i) {
    cur = find(n, cur, 2);
    if (wrap = in.count(cur)) break;
    in.insert(cur);
  }
  in.insert(0);
  if (!wrap) {
    for (int i = 0; i < n; ++i) if (!in.count(i) && qry(i, 1)) in.insert(i);
    for (int i = 0; i < n; ++i) if (!in.count(i) && (qry(i, big) || qry(i, big - 250))) in.insert(i);
  } else {
    for (int i = 0; i < n; ++i) if (!in.count(i) && (qry(i, big) || qry(i, big - 1))) in.insert(i);
  }
  cout << "! " << in.size();
  for (int num : in) cout << ' ' << num + 1;
  cout << endl;
  return 0;
}