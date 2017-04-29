import java.io.IOException;

/**
 * Created by Tenorio on 4/24/2017.
 */
public class Interpreter {


    private ParserV2 par;

    public Interpreter(String filename){
        par = new ParserV2(filename);
        try {
            par.populateList();
        } catch (IOException e) {
            e.printStackTrace();
        }
        par.printT();
    }


}
