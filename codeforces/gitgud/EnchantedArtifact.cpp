#include <bits/stdc++.h>
using namespace std;

int main() {
  // Finds the length of the string:
  string q = "a";
  printf("%s\n", q.c_str());
  fflush(stdout);
  int n; scanf("%d", &n);
  ++n;
  // Takes care of the special case where the string is 300 "b"s:
  if (n > 300) {
    string guess = ""; for (int i = 1; i < n; ++i) guess += "b";
    printf("%s\n", guess.c_str());
    fflush(stdout);
    return 0;
  }
  string guess = ""; for (int i = 0; i < n; ++i) guess += "a";
  printf("%s\n", guess.c_str());
  fflush(stdout);
  int res; scanf("%d", &res);
  // Takes care of the special cases where the string is all "b"s:
  if (res == n) {
    guess = ""; for (int i = 1; i < n; ++i) guess += "b";
    printf("%s\n", guess.c_str());
    fflush(stdout);
    return 0;
  }
  int ind = 0;
  while (res) {
    // Checks if letter at (ind) is a "b":
    guess[ind] = 'b';
    printf("%s\n", guess.c_str());
    fflush(stdout);
    int newRes; scanf("%d", &newRes);
    if (newRes > res) guess[ind] = 'a';
    else res = newRes;
    ++ind;
  }
  return 0;
}
