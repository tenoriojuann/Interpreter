/**
 * Created by Tenorio on 4/24/2017.
 */
public class Main{

    public static void main(String[] args) {

        try {



            Interpreter in = new Interpreter(Main.class.getResource("Sample.lua").getPath());
        }
       catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
