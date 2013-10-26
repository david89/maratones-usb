import java.util.*;

public class Generator {

      public static final int
            CANT_EJEMPLOS     = 2,
            CANT_CASOS        = 100,
            CANT_C            = 20,
            EACH_C            = 100,
            MAX_W             = 300,
            EPSILON           = 10;
      
      public static int boundedInt (Random R, int min, int max) {
            
            if (min < max)
                  return min + R.nextInt(max - min + 1);
            return min;
      }

      public static double getMin(int a, int b) {
            
            return Math.pow(Math.pow(a, 2.0/3.0) + Math.pow(b, 2.0/3.0), 3.0/2.0);
            
      }

      public static void main (String [] args) {
            
            Random R;
            boolean primero = true;
            
            R = new Random(System.currentTimeMillis());
            
            System.out.println(CANT_CASOS);
            
            int i;
            for (i = 0 ; i < CANT_EJEMPLOS; i++) {
                  if (!primero)
                        System.out.println();
                  primero = false;
                  System.out.print(Ejemplo.ejemplos[i]);
            }
            
            for ( ; i < CANT_CASOS ; i++) {
                  if (!primero)
                        System.out.println();
                  primero = false;
                  String tmp = "";
                  int C = boundedInt(R, 1, CANT_C);
                  tmp += C + "\n";
                  double mini = Double.POSITIVE_INFINITY;
                  int ant = boundedInt(R, 1, EACH_C);
                  tmp += ant + "";
                  C--;
                  while (C-- > 0) {
                        int next = boundedInt(R, 1, EACH_C);
                        tmp += " " + next;
                        mini = Math.min(mini, getMin(ant, next));
                        ant = next;
                  }
                  int W = 300;
                  if (boundedInt(R, 0, 100) <= 50) {
                        // Caso: Éxito.
                        W = Math.min(W, (int)(mini - boundedInt(R, 1, EPSILON)));
                        tmp += "\n" + W;
                  } else {
                        // Caso: Fracaso.
                        W = Math.min(W, (int)(mini + boundedInt(R, 1, EPSILON)));
                        tmp += "\n" + W;
                  }
                  System.out.print(tmp);
            }
            
      }
      
      private static class Ejemplo {
      
            public static Ejemplo[] ejemplos = new Ejemplo[CANT_EJEMPLOS];
      
            public int C, W;
      
            public int[] Cs;
      
            static {
                  // Caso 0:
                  ejemplos[0] = new Ejemplo (
                        2,
                        new int [] {
                              27, 64
                        },
                        125
                  );
                  
                  // Caso 1:
                  ejemplos[1] = new Ejemplo (
                        3,
                        new int [] {
                              64, 27, 64
                        },
                        126
                  );
            }
            
            public Ejemplo (int C, int[] Cs, int W) {
                  
                  this.C = C;
                  this.Cs = Cs;
                  this.W = W;
                  
            }
      
            @Override
            public String toString () {
                  
                  String ret = "";
                  boolean primero = true;
                  
                  ret += C + "\n";
                  for (int i = 0 ; i < C ; i++) {
                        if (!primero)
                              ret += " ";
                        primero = false;
                        ret += Cs[i] + ""; 
                  }
                  ret += "\n" + W;
                  
                  return ret;
                  
            }
      
      }
      
}