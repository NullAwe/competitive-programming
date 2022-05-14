#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

#define ll long long

inline int count(string str) {
  int ans = 0;
  for (int i = 0; i < str.size(); ++i) if (str[i] == '1') ++ans;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m, p; cin >> n >> m >> p;
  vector<string> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
  shuffle(arr.begin(), arr.end(), default_random_engine{});
  string ans(m, '0');
  for (int iter = 0; iter < 30; ++iter) {
    string picked = arr[rand() % n];
    vector<int> bits; bits.reserve(p);
    for (int i = 0; i < m; ++i) if (picked[i] == '1') bits.push_back(i);
    int size = bits.size();
    vector<int> counter(1 << size);
    for (int i = 0; i < n; ++i) {
      int index = 0;
      for (int j = 0; j < size; ++j) if (picked[bits[j]] == arr[i][bits[j]]) index |= (1 << j);
      ++counter[index];
    }
    for (int i = 0; i < (1 << size); ++i) {
      int anti = 0;
      for (int j = 0; j < size; ++j) if (!(i & (1 << j))) anti |= (1 << j);
      for (int add = anti; add > 0; add = (add - 1) & anti) counter[i] += counter[i | add];
    }
    int index = -1;
    for (int i = 0; i < (1 << size); ++i) if (counter[i] > (n - 1) / 2 && (index < 0 || __builtin_popcount(i) > __builtin_popcount(index))) index = i;
    if (index < 0) continue;
    string contender(m, '0');
    for (int i = 0; i < size; ++i) if (index & (1 << i)) contender[bits[i]] = '1';
    if (count(contender) > count(ans)) ans = contender;
  }
  cout << ans << '\n';
}
