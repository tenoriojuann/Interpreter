import java.io.*;


public class Analyzer {

    private FileInputStream url;
    private BufferedReader sb;
    private char ch;
    private static char EOF = (char) (-1);


    public Analyzer(FileInputStream url){

        openFile(url);

        ch = read();
    }

    public void openFile(FileInputStream url){
        this.url = url;
        sb = new BufferedReader(new InputStreamReader(url));
    }



    // Reads character by character
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
                        case '-':
                            ch = read();
                            state = 7;
                            continue;

                    }

                //  The case for when a number is scanned
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

                // Number is found by itself
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

                // Either a keyword is found or there is an invalid input
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

                // Keyword is found or a variable
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

                // A boolean comparison is found or an assignment
                case 6:
                    if(ch == '='){
                        ch = read();
                        return new Token("EQ","==");
                    }
                    else {
                        return new Token("AS", "=");
                    }


                // Found a comment
                case 7:
                    if(ch == '-'){
                        ch = read();
                        return new Token("CM","--");
                    }
                    ch = read();
                    continue;
                case 8:
                    if(ch == '\n'){
                        state =1;
                    }
                    ch = read();
                    continue;

            }
        }
    }


}
