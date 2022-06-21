#include <bits/stdc++.h>
using namespace std;

int maxPow(int j, int i) {
  int div = 0;
  while (j % i == 0) {
    j /= i;
    div++;
  }
  return div;
}

int main() {
  int n, max = 0;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
    max = std::max(max, nums[i]);
  }
  vector<vector<int>> sieve(max + 1);
  for (int i = 0; i <= max; i++) {
    vector<int> arr(8);
    sieve[i] = arr;
  }
  vector<int> indices(max + 1);
  for (int i = 2; i <= max; i++) {
    if (indices[i] > 0) continue;
    for (int j = i; j <= max; j+= i) sieve[j][indices[j]++] += maxPow(j, i);
  }
  vector<int> firsts(max + 1);
  int ind = 0;
  for (vector<int> arr : sieve) {
    int mult = 1;
    for (int num : arr) mult *= num + 1;
    firsts[ind++] = mult;
  }
  for (int i = 0; i < n; i++ ) cout << firsts[nums[i]] << "\n";
  return 0;
}

