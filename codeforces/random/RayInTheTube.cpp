#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;


struct customhash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, tmp; cin >> n >> tmp;
  vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
  int m; cin >> m >> tmp;
  vector<int> b(m); for (int i = 0; i < m; ++i) cin >> b[i];
  int ans = 0;
  for (int skip = 2; skip < 1e9; skip <<= 1) {
    vector<int> mods;
    gp_hash_table<int, int, customhash> modded;
    gp_hash_table<int, int, customhash> ma, mb;
    for (int num : a) {
      int val = num % skip;
      if (modded[val] != 100) {
        modded[val] = 100;
        mods.push_back(num % skip);
      }
      ++ma[val];
    }
    for (int num : b) {
      int val = num % skip;
      if (modded[val] != 100) {
        modded[val] = 100;
        mods.push_back(num % skip);
      }
      ++mb[val];
    }
    for (int mod : mods) ans = max(ans, max(ma[mod] + mb[(mod + skip / 2) % skip], ma[(mod + skip / 2) % skip] + mb[mod]));
  }
  if (ans == 1) {
    gp_hash_table<int, int, customhash> has; for (int num : b) has[num] = 100;
    for (int num : a) {
      if (has[num] == 100) {
        ans = 2;
        break;
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
