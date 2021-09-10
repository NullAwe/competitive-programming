import java.util.*;
 
public class Towers {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int[] nums = new int[n];
    for (int i = 0; i < n; i++) nums[i] = sc.nextInt();
    TreeMap<Integer, Integer> tm = new TreeMap<>();
    for (int num : nums) {
      // Finds the smallest stack which you can place the next element on:
      Map.Entry<Integer, Integer> hi = tm.higherEntry(num);
      if (hi != null) {
        if (hi.getValue() == 1) tm.remove(hi.getKey());
        else tm.put(hi.getKey(), hi.getValue() - 1);
      }
      tm.put(num, tm.getOrDefault(num, 0) + 1);
    }
    int ans = 0;
    for (Map.Entry<Integer, Integer> entry : tm.entrySet()) ans += entry.getValue();
	// Output:
    System.out.println(ans);
  }
}