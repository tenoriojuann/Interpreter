import java.io.*;

/**
 * Created by I859979 on 2/13/2017.
 */
public class Analyzer {

    FileInputStream url;
    BufferedReader sb;

    public Analyzer(){


    }

    public enum TYPES {
        integer, INT;
    }

    public void openFile(FileInputStream url){
        this.url = url;
        sb = new BufferedReader(new InputStreamReader(url));
    }

    public String getLine() throws IOException {
        if (sb.readLine() == null){
            return null;
        }
        else {
            return sb.readLine();
        }
    }

    public String[] SplitLine(String line){
        return line.split(" ");
    }

}
