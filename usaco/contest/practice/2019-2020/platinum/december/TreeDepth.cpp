#include <bits/stdc++.h>
using namespace std;

#define ll long long

int MOD;

void mult(vector<ll>& arr, int len) {
  arr.resize(arr.size() + len);
  for (int i = arr.size() - 1; i > len; --i) arr[i] = (arr[i] - arr[i - len - 1] + MOD) % MOD;
  for (int i = 1; i < arr.size(); ++i) arr[i] = (arr[i] + arr[i - 1]) % MOD;
}

void div(vector<ll>& arr, int len) {
  for (int i = arr.size() - 1; i > 0; --i) arr[i] = (arr[i] - arr[i - 1] + MOD) % MOD;
  for (int i = len + 1; i < arr.size(); ++i) arr[i] = (arr[i] + arr[i - len - 1]) % MOD;
  arr.resize(arr.size() - len);
}

int main() {
  ifstream in("treedepth.in");
  ofstream out("treedepth.out");
  int n, k; in >> n >> k >> MOD;
  vector<ll> arr(1, 1), ans(n); for (int i = 0; i < n; ++i) mult(arr, i);
  for (int diff = 0; diff < n; ++diff) {
    div(arr, diff);
    for (int i = diff; i < n; ++i) ans[i] = (ans[i] + arr[k]) % MOD;
    if (diff && k - diff >= 0) for (int i = 0; i + diff < n; ++i) ans[i] = (ans[i] + arr[k - diff]) % MOD;
    mult(arr, diff);
  }
  string str;
  for (ll num : ans) str += to_string(num) + " ";
  str.resize(str.size() - 1);
  out << str << '\n';
  return 0;
}
