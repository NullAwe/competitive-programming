#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("cardgame.in");
  ofstream out("cardgame.out");
  int n; in >> n;
  vector<int> elsie(n); for (int i = 0; i < n; ++i) in >> elsie[i];
  vector<bool> used(2 * n + 1); for (int num : elsie) used[num] = true;
  int ind = 0;
  vector<int> bessie(n); for (int i = 1; i <= 2 * n; ++i) if (!used[i]) bessie[ind++] = i;
  // Uses the largest half of values for the first half of the game: 
  set<int> first;
  for (int i = n / 2; i < n; ++i) first.insert(bessie[i]);
  int won = 0;
  // Finds winning rounds using a greedy strategy:
  for (int i = 0; i < n / 2; ++i) {
    auto it = first.upper_bound(elsie[i]);
    if (it == first.end()) first.erase(first.begin());
    else {
      ++won;
      first.erase(it);
    }
  }
  // Uses the smallest half of values for the second half of the game:
  set<int> second;
  for (int i = 0; i < n / 2; ++i) second.insert(bessie[i]);
  // Finds winning rounds using a greedy strategy:
  for (int i = n / 2; i < n; ++i) {
    auto it = second.upper_bound(elsie[i]);
    if (it == second.begin()) it = second.end();
    else ++won;
    --it;
    second.erase(it);
  }
  // Output:
  out << won << endl;
  return 0;
}
