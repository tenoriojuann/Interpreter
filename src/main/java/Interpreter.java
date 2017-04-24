import java.io.IOException;

/**
 * Created by Tenorio on 4/24/2017.
 */
public class Interpreter {


    private Parser par;

    public Interpreter(String filename){
        par = new Parser(filename);
        try {
            par.populateList();
        } catch (IOException e) {
            e.printStackTrace();
        }
        par.printT();
    }


}
