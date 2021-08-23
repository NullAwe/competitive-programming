import java.io.*;
import java.util.*;

public class MaximizeTheRemainingString {

  private static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
  private static PrintWriter out = new PrintWriter(System.out);

  public static void main(String[] args) throws IOException {
    int t = Integer.parseInt(in.readLine());
    for (int i = 0; i < t; i++) solve();
    out.close();
  }

  private static void solve() throws IOException {
    String str = in.readLine();
    int n = str.length();
    // Finds the character set of str:
    boolean[] has = new boolean[26];
    for (int i = 0; i < n; i++) has[str.charAt(i) - 'a'] = true;
    int cHas = 0;
    for (boolean b : has) if (b) cHas++;
    // Builds the answer:
    StringBuilder ans = new StringBuilder();
    boolean[] done = new boolean[26];
    int start = 0;
    for (int i = 0; i < cHas; i++) {
      // Finds the largest valid next character:
      for (int j = 25; j >= 0; j--) {
        if (done[j]) continue;
        // Finds character set of ans if our next character is j:
        boolean[] thisHas = Arrays.copyOf(done, done.length);
        int ind = -1;
        for (int k = start; k < n; k++) {
          if (str.charAt(k) - 'a' == j) {
            ind = k;
            break;
          }
        }
        if (ind < 0) continue;
        for (int k = ind; k < n; k++) thisHas[str.charAt(k) - 'a'] = true;
        if (!Arrays.equals(thisHas, has)) continue;
        // Updates ans because j is a valid next character:
        ans.append((char) (j + 'a'));
        done[j] = true;
        start = ind + 1;
        break;
      }
    }
    // Output:
    out.println(ans);
  }
}
