#include <bits/stdc++.h>
#include "library.h"
using namespace std;

void Solve(int n) {
  vector<int> front, back, left;
  for (int i = 0; i < n; ++i) left.push_back(i);
  while (left.size()) {
    int l = 0, r = left.size();
    while (l < r - 1) {
      int mid = (l + r) >> 1;
      vector<int> first(n), second(n);
      for (int i = 0; i < left.size(); ++i) {
        if (i >= l && i < mid) first[left[i]] = 1;
        else second[left[i]] = 1;
      }
      int q1 = Query(first), q2 = Query(second);
      if (q1 >= q2) r = mid;
      else l = mid;
    }
    int val = left[l], ind = 0;
    for (int i = 0; i < left.size(); ++i) if (left[i] == val) ind = i;
    left.erase(left.begin() + ind);
    if (front.size()) {
      vector<int> arr(n);
      arr[front.back()] = 1, arr[val] = 1;
      int q = Query(arr);
      if (q == 1) front.push_back(val);
      else back.push_back(val);
    } else front.push_back(val);
  }
  vector<int> ans;
  for (int num : front) ans.push_back(num + 1);
  reverse(back.begin(), back.end());
  for (int num : back) ans.push_back(num + 1);
  Answer(ans);
}