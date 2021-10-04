#include <bits/stdc++.h>
using namespace std;

#define ll long long

int floor(vector<int>& bales, ll val) {
  int lo = -1, hi = bales.size();
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    if (bales[mid] <= val) lo = mid;
    else hi = mid;
  }
  return lo;
}

int main() {
  ifstream in("angry.in");
  ofstream out("angry.out");
  int n; in >> n;
  vector<int> bales(n); for (int i = 0; i < n; ++i) in >> bales[i];
  for (int i = 0; i < n; ++i) bales[i] *= 2;
  sort(bales.begin(), bales.end());
  vector<int> diffs(n - 1);
  for (int i = 0; i < n - 1; ++i) diffs[i] = bales[i + 1] - bales[i];
  vector<int> pref(n);
  int ts = 2, cur = 0;
  for (int i = 0; i < n - 1; ++i) {
    if (cur + diffs[i] > ts) {
      pref[i + 1] = max(ts + 2, diffs[i]);
      ts = pref[i + 1];
      cur = diffs[i];
    } else {
      pref[i + 1] = ts;
      cur += diffs[i];
    }
  }
  vector<int> suff(n);
  ts = 2, cur = 0;
  for (int i = n - 1; i > 0; --i) {
    if (cur + diffs[i - 1] > ts) {
      suff[i - 1] = max(ts + 2, diffs[i - 1]);
      ts = suff[i - 1];
      cur = diffs[i - 1];
    } else {
      suff[i - 1] = ts;
      cur += diffs[i - 1];
    }
  }
  // Finds answer by using binary search:
  ll lo = 0, hi = 2000000001;
  while (lo < hi - 1) {
    ll mid = (lo + hi) / 2;
    bool works = false;
    for (int i = 0; i < n; ++i) {
      int fl = floor(bales, bales[i] + mid * 2);
      if (max(pref[i], suff[fl]) + 2 <= mid) {
        works = true;
        break;
      }
    }
    if (works) hi = mid;
    else lo = mid;
  }
  // Output:
  out << hi / 2 << '.' << (hi % 2 == 0 ? 0 : 5) << endl;
  return 0;
}
