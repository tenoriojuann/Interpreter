import java.io.IOException;
import java.io.FileWriter;
import java.util.Deque;
import java.util.LinkedList;

/**
 * Created by Tenorio on 4/24/2017.
 */
public class Interpreter  {


    private Parser par;
    //Main.class.getResource("Sample.lua").getPath()

    public Interpreter(String filename)throws IOException{
        FileWriter writer= new FileWriter(Main.class.getResource("ex.java").getPath());

        par = new Parser(filename);

        //LinkedList<Token>
       // LinkedList<LinkedList<Token>>[] arr;
        try {
            par.populateList();
            //par.list.toArray();
        } catch (IOException e) {
            e.printStackTrace();
        }
        par.printT();
        writer.write("import java.io.IOException; \n" +
                "import java.util.*; \n" +
                "public class Main{\n" +
                "public static void main(String[] args){\n");
        for (LinkedList<Token> queue : par.list) {
            // for every token in the queue
            for (Token token : queue) {
                writer.write(token.getLexeme());
            }
            writer.write("\n");
        }
        writer.write("}\n}\n");
writer.close();
    }


}
