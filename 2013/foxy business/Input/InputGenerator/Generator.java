import java.util.*;

public class Generator {

      public static final int
            CANT_EJEMPLOS     = 2,
            CANT_CASOS        = 200,
            CANT_LINEAS       = 20,
            LONG_STR          = 50,
            CHANCE_FOX        = 80;
      
      public static int boundedInt (Random R, int min, int max) {
            
            if (min < max)
                  return min + R.nextInt(max - min + 1);
            return min;
      }

      public static void main (String [] args) {
            
            Random R;
            boolean primero = true;
            
            R = new Random(System.currentTimeMillis());
            
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
                  int num_lineas = boundedInt(R, 1, CANT_LINEAS);
                  int linea_fox = -1;
                  if (boundedInt(R, 0, 100) <= CHANCE_FOX)
                        linea_fox = boundedInt(R, 0, num_lineas);
                  for (int j = 0 ; j < num_lineas ; j++) {
                        int long_animal = boundedInt(R, 1, LONG_STR);
                        char[] animal = new char[long_animal];
                        if (j != linea_fox) {
                              for (int k = 0 ; k < long_animal ; k++) {
                                    int despl = boundedInt(R, 0, 26);
                                    if (despl < 26)
                                          animal[k] = (char)('a' + despl);
                                    else
                                          animal[k] = ' ';
                              }
                        }
                        int long_sound = boundedInt(R, 1, LONG_STR);
                        char[] sound = new char[long_sound];
                        for (int k = 0 ; k < long_sound ; k++) {
                              int despl = boundedInt(R, 0, 30);
                              if (despl < 26)
                                    sound[k] = (char)('a' + despl);
                              else
                                    sound[k] = ' ';
                        }
                        String tmp = "The ";
                        if (j == linea_fox)
                              tmp += "fox";
                        else
                              tmp += new String(animal).trim();
                        tmp += " goes " + new String(sound).trim() + "\n";
                        System.out.print(tmp);
                  }
                  System.out.print("What does the fox say?");
            }
            
      }
      
      private static class Ejemplo {
      
            public static Ejemplo [] ejemplos = new Ejemplo[CANT_EJEMPLOS];
      
            public String[] animals, sounds;
      
            static {
                  // Caso 0:
                  ejemplos[0] = new Ejemplo (
                        new String [] {
                              "cat", "dog", "fox", "cow"
                        },
                        new String [] {
                              "meow", "woof woof", "ring a ding ding", "moo"
                        }
                  );
                  
                  // Caso 1:
                  ejemplos[1] = new Ejemplo (
                        new String [] {
                              "little duck", "big elephant"
                        },
                        new String [] {
                              "quack", "toot"
                        }
                  );
            }
            
            public Ejemplo (String[] animals, String[] sounds) {
                  
                  this.animals = animals;
                  this.sounds = sounds;
                  
            }
      
            @Override
            public String toString () {
                  
                  String ret = "";
                  
                  for (int i = 0 ; i < animals.length ; i++)
                        ret += "The " + animals[i] + " goes " + sounds[i] + "\n"; 
                  
                  ret += "What does the fox say?";
                  
                  return ret;
                  
            }
      
      }
      
}