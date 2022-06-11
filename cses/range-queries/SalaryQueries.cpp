#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

vector<int> t;
int sz;

void modify(int p, int c) {
  for (t[p += sz] += c; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

int query(int l, int r) {
  int ans = 0;
  for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

int main() {
  int n, q; cin >> n >> q;
  vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  vector<int> sorted; sorted.reserve(n + 2 * q);
  for (int num : arr) sorted.push_back(num);
  vector<pair<char, pii>> qs(q);
  for (int i = 0; i < q; ++i) {
    char type; cin >> type;
    int a, b; cin >> a >> b;
    qs[i] = {type, {a, b}};
    sorted.push_back(b);
    if (type == '?') sorted.push_back(a);
  }
  sort(sorted.begin(), sorted.end());
  sz = sorted.size();
  for (int i = 0; i < n; ++i) arr[i] = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin();
  t.resize(2 * sz);
  for (int i = 0; i < n; ++i) modify(arr[i], 1);
  for (int i = 0; i < q; ++i) {
    int a = qs[i].second.first, b = qs[i].second.second;
    if (qs[i].first == '!') {
      --a;
      modify(arr[a], -1);
      arr[a] = lower_bound(sorted.begin(), sorted.end(), b) - sorted.begin();
      modify(arr[a], 1);
    } else {
      a = lower_bound(sorted.begin(), sorted.end(), a) - sorted.begin(), b = lower_bound(sorted.begin(), sorted.end(), b) - sorted.begin();
      cout << query(a, b + 1) << '\n';
    }
  }
  return 0;
}

