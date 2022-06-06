#include <bits/stdc++.h>
using namespace std;
 
int bs(vector<int>& nums, int num) {
  int lo = 0, hi = nums.size() - 1;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    if (nums[mid] < num) lo = mid;
    else hi = mid;
  }
  return hi;
}
 
int main() {
  int n;
  cin >> n;
  if (n < 2) {
    cout << n << "\n";
    return 0;
  }
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) cin >> nums[i];
  vector<int> cur;
  cur.push_back(nums[0]);
  for (int i = 1; i < n; ++i) {
    if (nums[i] <= cur[0]) cur[0] = nums[i];
    else if (nums[i] > cur[cur.size() - 1]) cur.push_back(nums[i]);
    else cur[bs(cur, nums[i])] = nums[i];
  }
  cout << cur.size() << "\n";
  return 0;
}
