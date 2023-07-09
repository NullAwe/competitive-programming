#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define pii pair<int, int>

void solve(int t) {
  int n; cin >> n;
  vector<pii> arr(n);
  for (int i = 0; i < n; ++i) cin >> arr[i].first;
  for (int i = 0; i < n; ++i) arr[i].second = i;
  vector<int> count(n + 1); for (pii num : arr) ++count[num.first];
  set<int> curs;
  for (int num : count) {
    if (num > (n + 1) / 2) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
  int cur = 0;
  while (cur < n) {
    curs.insert(n - cur - 1);
    int last, cl = 0;
    for (last = cur; last < n; ++last) {
      cl += arr[last].first == arr[cur].first;
      if (cl == (last - cur + 2) / 2 && (last - cur) % 2 == 0 && (last == n - 1 || arr[last + 1].first != arr[cur].first)) break;
    }
    if (last == n) break;
    vector<pii> ord1, ord2;
    for (int i = cur; i <= last; ++i) {
      if (arr[i].first == arr[cur].first) ord1.push_back(arr[i]);
      else ord2.push_back(arr[i]);
    }
    int i1 = 0, i2 = 0;
    for (int i = cur; i <= last; ++i) {
      if ((i - cur) & 1) arr[i] = ord2[i2++];
      else arr[i] = ord1[i1++];
    }
    cur = last + 1;
  }
  curs.insert(n - cur - 1);
  vector<pii> copy = arr;
  int curCopy = cur;
  bool on = false;
  if (cur < n) {
    int num = arr[cur].first;
    reverse(arr.begin(), arr.end());
    int last, cl = 0, fl = n - cur - 1;
    cur = 0;
    for (last = cur; last < n; ++last) {
      cl += arr[last].first == arr[fl].first;
      if (curs.count(last)) on = true;
      if (cl == (last - cur + 2) / 2 && (last == n - 1 || arr[last + 1].first != arr[fl].first) && last > fl && on) break;
      on = !on;
    }
    for (int i = cur; i <= last; ++i) swap(arr[i].first, arr[i].second);
    sort(arr.begin(), arr.begin() + last + 1);
    for (int i = cur; i <= last; ++i) swap(arr[i].first, arr[i].second);
    vector<pii> ord1, ord2;
    for (int i = cur; i <= last; ++i) {
      if (arr[i].first == num) ord1.push_back(arr[i]);
      else ord2.push_back(arr[i]);
    }
    int i1 = 0, i2 = 0;
    for (int i = cur; i <= last; ++i) {
      if ((i - cur) & 1) arr[i] = ord2[i2++];
      else arr[i] = ord1[i1++];
    }
    reverse(arr.begin(), arr.begin() + last + 1);
    reverse(arr.begin(), arr.end());
  }
  for (pii num : arr) cout << num.second + 1 << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve(i);
  return 0;
}