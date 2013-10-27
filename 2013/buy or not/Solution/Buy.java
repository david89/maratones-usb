import java.util.*;

public class Buy {

      public static double EPSILON = 1e-3;

      public static double getMin(int a, int b) {
            
            return Math.pow(Math.pow(a, 2.0/3.0) + Math.pow(b, 2.0/3.0), 3.0/2.0);
            
      }

      public static void main (String [] args) {
            
            Scanner S = new Scanner (System.in);
            int T = S.nextInt();
            while (T-- > 0) {
                  int C = S.nextInt() - 1;
                  int ant = S.nextInt();
                  double mini = Double.POSITIVE_INFINITY;
                  while (C-- > 0) {
                        int next = S.nextInt();
                        mini = Math.min(mini, getMin(ant, next));
                        ant = next;
                  }
                  int W = S.nextInt();
                  if (W <= mini + EPSILON)
                        System.out.println("I'll buy it!");
                  else
                        System.out.println("Bah! I didn't even want it!");
            }
            
      }

}