#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<vector<int>> getCombs(int start, int end, int k) {
  vector<vector<int>> ans;
  if (k == 1) {
    for (int i = start; i < end; ++i) {
      vector<int> add;
      add.push_back(i);
      ans.push_back(add);
    }
    return ans;
  }
  // Iterates through all possible last numbers:
  for (int i = end - 1; i >= start + k - 1; --i) {
    vector<vector<int>> next = getCombs(start, i, k - 1);
    for (vector<int> comb : next) {
      comb.push_back(i);
      ans.push_back(comb);
    }
  }
  return ans;
}

// Finds the number of numbers coprime to n less than m:
ll getRP(ll n, ll m, vector<ll>& factors) {
  ll coprime = m, sign = 1;
  for (int i = 1; i <= factors.size(); ++i) {
    sign = -sign;
    vector<vector<int>> combs = getCombs(0, factors.size(), i);
    for (vector<int> comb : combs) {
      ll mult = 1;
      for (int num : comb) mult *= factors[num];
      coprime += sign * (m / mult);
    }
  }
  return coprime;
}

ll GCD(ll a, ll b) {
  if (b == 0) return a;
  return GCD(b, a % b);
}

bool isPrime(ll n) {
  for (ll i = 2; i * i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

void solve() {
  ll a, m; cin >> a >> m;
  // If m is prime all values of x other than m - a will be valid.
  if (isPrime(m)) {
    cout << m - 1 << endl;
    return;
  }
  ll div = GCD(a, m);
  a /= div;
  m /= div;
  // Finds the factors of m:
  vector<ll> factors;
  ll tmp = m;
  for (ll i = 2; i * i <= tmp; ++i) {
    if (tmp % i == 0) {
      factors.push_back(i);
      while (tmp % i == 0) tmp /= i;
    }
  }
  if (tmp > 1) factors.push_back(tmp);
  // Answer is number of numbers coprime to m in the range (a, a + m]:
  cout << getRP(m, a + m, factors) - getRP(m, a - 1, factors) - 1 << endl;
}

int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}
