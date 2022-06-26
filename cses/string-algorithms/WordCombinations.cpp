#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct TrieNode {

  char val;
  vector<TrieNode*> c;

  bool done = false;

  TrieNode(char val) : val(val), c(26, nullptr) {}

  void add(string& word, int i) {
    if (i >= word.size()) {
      done = true;
      return;
    }
    if (!c[word[i] - 'a']) c[word[i] - 'a'] = new TrieNode(word[i]);
    c[word[i] - 'a']->add(word, i + 1);
  }
};

struct Trie {

  TrieNode* root;

  Trie() {
    root = new TrieNode(' ');
  }

  void add(string& word) {
    root->add(word, 0);
  }
};

int main() {
  string s; cin >> s;
  int n = s.size(), k; cin >> k;
  Trie trie;
  for (int i = 0; i < k; ++i) { string str; cin >> str; trie.add(str); }
  vector<int> dp(n + 1); dp[n] = 1;
  for (int i = n - 1; i >= 0; --i) {
    TrieNode* at = trie.root;
    for (int j = i; j < n; ++j) {
      at = at->c[s[j] - 'a'];
      if (!at) break;
      if (at->done) dp[i] = (dp[i] + dp[j + 1]) % MOD;
    }
  }
  cout << dp[0] << '\n';
  return 0;
}
