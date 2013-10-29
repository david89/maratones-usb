import java.util.*;

public class Generator {

      public static final int
            CANT_EJEMPLOS     = 7,
            CANT_CASOS        = 100,
            MAX_N             = 10,
            MAX_K             = 3;
      
      public static int boundedInt (Random R, int min, int max) {
            
            if (min < max)
                  return min + R.nextInt(max - min + 1);
            return min;
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
                  int n = boundedInt(R, 1, MAX_N),
                      k = boundedInt(R, 1, MAX_K);
                  System.out.print(n + " " + k);
            }
            
      }
      
      private static class Ejemplo {
      
            public static Ejemplo[] ejemplos = new Ejemplo[CANT_EJEMPLOS];
      
            public int n, k;
      
            static {
                  // Caso 0:
                  ejemplos[0] = new Ejemplo (
                        3,
                        2
                  );
                  
                  // Caso 1:
                  ejemplos[1] = new Ejemplo (
                        2,
                        2
                  );
                  
                  // Caso 2:
                  ejemplos[2] = new Ejemplo (
                        5,
                        3
                  );
                  
                  // Caso 3:
                  ejemplos[3] = new Ejemplo (
                        10,
                        3
                  );
                  
                  // Caso 4:
                  ejemplos[4] = new Ejemplo (
                        5,
                        2
                  );
                  
                  // Caso 5:
                  ejemplos[5] = new Ejemplo (
                        6,
                        2
                  );
                  
                  // Caso 6:
                  ejemplos[6] = new Ejemplo (
                        2,
                        1
                  );
            }
            
            public Ejemplo (int n, int k) {
                  
                  this.n = n;
                  this.k = k;
                  
            }
      
            @Override
            public String toString () {
                  
                  return n + " " + k;
                  
            }
      
      }
      
}