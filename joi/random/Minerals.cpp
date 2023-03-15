#include <bits/stdc++.h>
#include "minerals.h"
using namespace std;
 
vector<bool> on;
int ans;
 
void solve(vector<int> a, vector<int> b) {
  if (a.size() == 1) {
    Answer(a[0], b[0]);
    return;
  }
  int n = a.size() / 2.61803398875;
  if (n == 0) n = 1;
  int m = a.size() - n;
  if (on[a[0]]) swap(n, m);
  vector<int> a1(n), a2(m);
  vector<int> b1, b2;
  for (int i = 0; i < n; ++i) a1[i] = a[i];
  for (int i = 0; i < m; ++i) a2[i] = a[i + n];
  for (int i : a1) if (!on[i]) ans = Query(i), on[i] = 1;
  for (int i : a2) if (on[i]) ans = Query(i), on[i] = 0;
  for (int i : b) {
    if (b1.size() == n) {
      b2.push_back(i);
      continue;
    }
    if (b2.size() == m) {
      b1.push_back(i);
      continue;
    }
    int now = Query(i);
    if (now == ans) b1.push_back(i);
    else b2.push_back(i);
    ans = now;
  }
  solve(a1, b1), solve(a2, b2);
}
 
void Solve(int n) {
  on.resize(2 * n + 1);
  vector<int> a, b;
  int last = 0;
  for (int i = 1; i <= 2 * n; ++i) {
    if (a.size() == n) {
      b.push_back(i);
      continue;
    }
    if (b.size() == n) {
      a.push_back(i);
      continue;
    }
    int now = Query(i);
    if (now > last) a.push_back(i), on[i] = 1;
    else b.push_back(i);
    last = ans = now;
  }
  solve(a, b);
}
