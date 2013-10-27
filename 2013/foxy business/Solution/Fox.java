import java.util.*;
import java.util.regex.*;

public class Fox {

      public static void main (String [] args) {
            
            Scanner S = new Scanner (System.in);
            Pattern p = Pattern.compile("The ([a-z ]+) goes ([a-z ]+)");
            String foxy = null;
            while (S.hasNext()) {
                  Matcher m = p.matcher(S.nextLine());
                  if (m.find()) {
                        String animal = m.group(1);
                        if (animal.equals("fox"))
                              foxy = m.group(2);
                  } else {
                        if (foxy == null)
                              System.out.println("will we ever know?");
                        else
                              System.out.println(foxy);
                        foxy = null;
                  }
            }
            
      }

}