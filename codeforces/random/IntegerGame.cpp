#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll nums[3];

void query(ll x) {
  cout << x << endl;
  int ans; cin >> ans;
  if (ans <= 0) exit(0);
  nums[ans - 1] += x;
}

int main() {
  cin >> nums[0] >> nums[1] >> nums[2];
  cout << "First" << endl;
  query(1e9);
  vector<ll> tmp(3);
  for (int i = 0; i < 3; ++i) tmp[i] = nums[i];
  sort(tmp.begin(), tmp.end());
  query(tmp[2] + (tmp[2] - tmp[0]) - tmp[1]);
  for (int i = 0; i < 3; ++i) tmp[i] = nums[i];
  sort(tmp.begin(), tmp.end());
  query(tmp[1] - tmp[0]);
  return 0;
}