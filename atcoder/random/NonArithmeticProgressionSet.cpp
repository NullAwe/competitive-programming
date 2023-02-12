#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n; cin >> n;
  ll k; cin >> k;
  bitset<100000000> cant;
  vector<int> has; has.push_back(1);
  int at = 1;
  while (has.size() < n - 1) {
    ++at;
    if (cant.test(at)) continue;
    for (int num : has) cant.set(2 * at - num, 1);
    has.push_back(at);
  }
  ++at;
  ll sum = 0;
  for (int num : has) sum += num;
  while (cant.test(at) || (sum + at - k) % n) ++at;
  has.push_back(at);
  sum += at;
  int diff = (sum - k) / n;
  for (int i = 0; i < n; ++i) has[i] -= diff;
  for (int num : has) cout << num << ' ';
  cout << '\n';
  return 0;
}