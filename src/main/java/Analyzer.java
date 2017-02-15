import java.io.*;

/**
 * Created by I859979 on 2/13/2017.
 */
public class Analyzer {

    FileInputStream url;
    BufferedReader sb;

    String[] splitLine;

    String[] OPERATORS = {"*","-","+","/","="};

    String[] TYPES = {"int", "integer"};

    public Analyzer(){


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

    public void SplitLine(String line) {
        splitLine = line.split(" ");
    }

    public String getType(){

        for(String type : TYPES) {
            if (type.equalsIgnoreCase(splitLine[0])){
                return type;
            }
        }
        return "var";
    }

    public String getOperator(){

        for(String op : OPERATORS){
            if(splitLine[1].equals(op)){
                return op;
            }
        }
        return "none";
    }

}
