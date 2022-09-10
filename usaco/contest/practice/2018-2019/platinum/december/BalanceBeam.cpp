#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>

const ll M = 100000;

int main() {
  ifstream in("balance.in");
  ofstream out("balance.out");
  int n; in >> n;
  vector<int> arr(n + 1); for (int i = 0; i < n; ++i) in >> arr[i];
  vector<pii> mx; mx.push_back({-1, 0});
  for (int i = 0; i <= n; ++i) {
    while (mx.size() > 1) {
      pii a = mx[mx.size() - 2], b = mx.back();
      pii c = {i - a.first, arr[i] - a.second}, d = {i - b.first, arr[i] - b.second};
      if ((ll) c.first * d.second < (ll) c.second * d.first) break;
      mx.resize(mx.size() - 1);
    }
    mx.push_back({i, arr[i]});
  }
  int l = 0;
  for (int i = 0; i < n; ++i) {
    if (l < mx.size() - 1 && mx[l + 1].first == i) {
      out << M * mx[l + 1].second << '\n';
      ++l;
      continue;
    }
    out << M * ((ll) mx[l].second * (mx[l + 1].first - i) + (ll) mx[l + 1].second * (i - mx[l].first)) / (mx[l + 1].first - mx[l].first) << '\n';
  }
  return 0;
}
