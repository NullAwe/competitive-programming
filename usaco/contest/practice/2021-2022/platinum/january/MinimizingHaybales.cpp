#include <bits/stdc++.h>
using namespace std;

const int SPLIT_SZ = 700;

int main() {
  int n, k; cin >> n >> k;
  vector<vector<int>> arr;
  vector<int> mns, mxs;
  int x; cin >> x;
  vector<int> add(1, x); arr.push_back(add);
  mns.push_back(x), mxs.push_back(x);
  for (int i = 1; i < n; ++i) {
    cin >> x;
    int j = arr.size() - 1, l;
    while (j >= 0 && mns[j] >= x - k && mxs[j] <= x + k) --j;
    if (j < 0) ++j;
    for (l = arr[j].size() - 1; l >= 0; --l) if (arr[j][l] < x - k || arr[j][l] > x + k) break;
    ++l;
    for (; l < arr[j].size(); ++l) if (arr[j][l] > x) break;
    if (l == arr[j].size()) {
      for (++j; j < arr.size(); ++j) if (mxs[j] > x) break;
      if (j == arr.size()) --j, l = arr[j].size();
      else for (l = 0; l < arr[j].size(); ++l) if (arr[j][l] > x) break;
    }
    arr[j].insert(arr[j].begin() + l, x);
    mns[j] = min(mns[j], x), mxs[j] = max(mxs[j], x);
    if (arr[j].size() < SPLIT_SZ) continue;
    vector<int> arr1(arr[j].size() / 2), arr2(arr[j].size() / 2);
    int mn1 = INT_MAX, mx1 = 0, mn2 = INT_MAX, mx2 = 0;
    for (int l = 0; l < arr[j].size() / 2; ++l) {
      mn1 = min(mn1, arr[j][l]), mx1 = max(mx1, arr[j][l]);
      arr1[l] = arr[j][l];
      int ind = l + arr[j].size() / 2;
      mn2 = min(mn2, arr[j][ind]), mx2 = max(mx2, arr[j][ind]);
      arr2[l] = arr[j][ind];
    }
    arr.erase(arr.begin() + j);
    arr.insert(arr.begin() + j, arr2), arr.insert(arr.begin() + j, arr1);
    mns.erase(mns.begin() + j);
    mns.insert(mns.begin() + j, mn2), mns.insert(mns.begin() + j, mn1);
    mxs.erase(mxs.begin() + j);
    mxs.insert(mxs.begin() + j, mx2), mxs.insert(mxs.begin() + j, mx1);
  }
  for (vector<int> nums : arr) for (int num : nums) cout << num << '\n';
  return 0;
}
