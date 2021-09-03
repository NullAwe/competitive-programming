import java.io.*;

public class DigitQueries {
	
  private static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
  private static PrintWriter out = new PrintWriter(System.out);

  public static void main(String[] args) throws IOException {
    int t = Integer.parseInt(in.readLine());
    for (int i = 0; i < t; i++) solve();
    out.close();
  }
  
  public static void solve() throws IOException {
    long n = Long.parseLong(in.readLine());
    long add = 1, sum = 0, next = sum + 9 * add * (long) Math.pow(10, add - 1);
    // Skip the numbers by number of digits:
    while (next < n && next > 0) {
      sum = next;
      add++;
      next = sum + 9 * add * (long) Math.pow(10, add - 1);
    }
    long left = n - sum, tmp = (left - 1) % add + 1;
    // Output:
    out.println(Long.toString((long) Math.pow(10, add - 1) + (left - 1) / add).charAt((int) tmp - 1));
  }
}
