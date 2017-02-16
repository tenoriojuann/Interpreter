import java.io.*;


public class Analyzer {

    private FileInputStream url;
    private BufferedReader sb;
    private char ch;
    private static char EOF = (char) (-1);

    String[] splitLine;

    String[] OPERATORS = {"*","-","+","/","="};

    String[] TYPES = {"int", "integer"};

    String[] KEYWORDS = {"and","else","false", "if", "nil","repeat", "true"
                         "break", "elseif", "for" , "in", "not", "return", "until",
                         "do", "end", "function", "local", "or", "then", "while"};

    String[] TOKENS;
    public Analyzer(FileInputStream url){

        openFile(url);

        ch = read();
    }

    public void openFile(FileInputStream url){
        this.url = url;
        sb = new BufferedReader(new InputStreamReader(url));
    }

    private char read(){
        try {
            return (char) (sb.read());
        } catch (IOException e) {
            e.printStackTrace();
            return EOF; // EOF
        }
    }

    public Token nextToken(){

        int state =1;
        int numBuffer =0;
        String alphaBuffer = "";
        int decBuffer=0;
        boolean skipped = false;
        while(true){

            if(ch == EOF && !skipped) { // EOF

                skipped = true;
            }
            else if(skipped) {
                try {
                    sb.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                return null;
            }

            switch (state){

                case 1:
                    switch (ch){
                        case ' ':
                            ch = read();
                            continue;
                        case '.':
                            ch = read();
                            return new Token("PD", ".");
                        case '+':
                            return new Token("SM","+");
                        case'=':
                            ch=read();
                            state=6;
                            continue;

                    }
                case 2:
                    if(Character.isDigit(ch)){
                        numBuffer = 0;
                        numBuffer += Character.getNumericValue(ch);

                        state = 3;

                        ch = read();
                    }
                    else{
                        state = 6;
                    }
                    continue;
                case 3:
                    if(Character.isDigit(ch)){
                        numBuffer *= 10;
                        numBuffer += Character.getNumericValue(ch);

                        ch = read();
                    }
                    else{
                        return new Token("NUM",String.valueOf(numBuffer));
                    }
                    continue;

                case 4:

                    if(Character.isAlphabetic(ch) || ch == '_') {

                        alphaBuffer = "";
                        alphaBuffer += ch;
                        state = 5;
                        ch = read();
                    }
                    else{
                        alphaBuffer = "";
                        alphaBuffer += ch;

                        ch = read();
                        return  new Token("INVALID","Invalid input: "+ alphaBuffer);
                    }
                    continue;
                case 5:

                    if(Character.isAlphabetic(ch) || Character.isDigit(ch) || ch == '_'){
                        alphaBuffer += ch;
                        ch = read();
                    }
                    else{
                        if(alphaBuffer.equals("int")) {
                            return new Token("KW", alphaBuffer);
                        }

                        return new Token("ID", alphaBuffer);
                    }

                    continue;

                case 6:
                    if(ch == '='){
                        ch = read();
                        return new Token("EQ","==");
                    }
                    else {
                        return new Token("AS", "=");
                    }

            }
        }
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

    // Probably moving this to the Parser.java class

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

    public boolean isComment(){
        for(String word : splitLine){
            if (word.contains("--")){
                return true;
            }

        }

        return false;
    }

}
