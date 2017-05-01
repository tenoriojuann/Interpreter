
import java.io.IOException;
import java.util.*;

public class Parser {


    private LinkedList<Token> tokens = new LinkedList();
    private LinkedList<LinkedList<Token>> list = new LinkedList();
    private String filename;
    public String pLast;
    public Parser(String filename) {
        this.filename = filename;
    }

    public void populateList() throws IOException {

        Lexer lex = new Lexer(filename);
        Token tok = lex.nextToken();
        tokens.addLast(tok);

        while (lex.fp.ready()) {
            //if(lex.fp.read()!=(-1)) {//Tried in case ready was not giving a false
            if (tokens.peekLast().getLexeme().equals("while")) {
                foundWHILE();
            } else if (tokens.peekLast().getLexeme().equals("if")) {
                foundIF();
            } else if (tokens.peekLast().getLexeme().equals("then")) {
                foundTHEN();
            } else if (tokens.peekLast().getToken().equals("ID")) {
                foundID();
            } else if (tokens.peekLast().getLexeme().equals("do")) {
                foundDO();
            } else if (tokens.peekLast().getLexeme().equals("end")) {
                foundEND();
            }


            // Checking for new LINE
            tok = lex.nextToken();

            // if (tok.getLexeme()!=("KW")) {//Was trying to stop if at end program was causing issue.
            if (tokens.peekLast().getLineNum() < tok.getLineNum()) {
                tokens.addLast(tok);
                newLine();
            } else {
                tokens.addLast(tok);

                if (tokens.size() > 0) {
                    if (tokens.peekLast().getLineNum() < tok.getLineNum()) {
                        tokens.addLast(tok);
                        newLine();
                    } else {
                        tokens.addLast(tok);
                    }
                } else {
                    tokens.addLast(tok);

                }
                // }


                //}

            }
            lex.fp.close();

        }
    }

    private void newLine() {
        //Token that belongs to the new line
        Token tmp = tokens.peekLast();
        tokens.removeLast();


        // checking special cases

        if (tmp.getLexeme().equals("end")) {
            foundEND();
        } else if (tmp.getLexeme().equals("do")) {

        if (tmp.getLexeme().equals( "do") ){

            foundDO();
        } else if (tmp.getLexeme().equals("if")) {

            list.addLast(new LinkedList<>());//because reference clear removed all tokens
            tokens.clear();
            tokens.addLast(tmp);
            foundIF();
        }/* else if (tmp.getToken().equals( "COM") ){
            list.addLast(new LinkedList<>(tokens));
            tokens.clear();
            tokens.addLast(tmp);
            foundCOMMENT();
        }*/

        // making sure there are no open/closed parenthesis or curly brackets
        else if (!tokens.peekLast().getToken().equals("LP")  && !tokens.peekLast().getToken().equals("LC")  && !tokens.peekLast().getToken().equals("RP")  ) {

            tokens.addLast(new Token("SEMI", ";", tokens.peekLast().getLineNum()));

            //list.addLast(new LinkedList<>(tokens));


            //Clearing the queue for the new line of the source code

            list.addLast(new LinkedList<>(tokens));

            // Clearing the queue for the new line of the source code
            tokens.clear();
            //Pushing the first token of the new line
            tokens.addLast(tmp);

        }

    }
    }

    // function for when a comment is found
    private void foundCOMMENT() {

        Token tmp = tokens.peekLast();
        tokens.removeLast();


        String st = tmp.getLexeme();
        String cm = null;
        int index = 0;
        for (char c : st.toCharArray()) {
            if (index > 1) {
                cm += c;
            }
            index++;
        }
        tmp.setLexeme(cm);
        tokens.addLast(tmp);
    }

    // function for when an END is found
    private void foundEND() {

        Token tmp = new Token("RC", "}", tokens.peekLast().getLineNum());
        if (tokens.peekLast().getLexeme().equals("end")) {

            tokens.removeLast();
            tokens.clear();
        }

        //**************************************************not sure why it doesn't need a clear.

        list.addLast(new LinkedList<>(tokens));
        tokens.clear();

        tokens.addLast(tmp);
        pLast="end";
        list.addLast(new LinkedList<>(tokens));

    }

    // function for when a  while loop is found
    private void foundWHILE() {

        tokens.addLast(new Token("LP", "(", tokens.peekLast().getLineNum()));
        pLast="while";
    }

    // function for when a DO is found
    private void foundDO() {

        tokens.removeLast();
        tokens.addLast(new Token("RP", ")", tokens.peekLast().getLineNum()));
        tokens.addLast(new Token("LC", "{", tokens.peekLast().getLineNum()));
        pLast="do";
    }

    // function for when an IF is found
    private void foundIF() {

        tokens.addLast(new Token("LP", "(", tokens.peekLast().getLineNum()));
        //list.addLast(new LinkedList<>());
        pLast="if";

    }

    // function for when an THEN is found
    private void foundTHEN() {

        Token tmp = tokens.peekLast();
        tokens.removeLast();
        tokens.addLast(new Token("RP", ")", tmp.getLineNum()));
        tokens.addLast(new Token("LC", "{", tmp.getLineNum()));


        list.addLast(new LinkedList<>(tokens));
        tokens.clear();
        tokens.addLast(tmp);
        pLast="then";


        list.addLast(new LinkedList<>(tokens));
        tokens.clear();


    }

    // function for when an comma is found
    private void foundCOMMA() {

        if (tokens.getFirst().getLexeme() != "local" || tokens.getFirst().getLexeme() != "type") {

            System.out.printf("ERROR ON LINE: %d Define kind of variable", tokens.getFirst().getLineNum());
        }
    }


    // function for when an variable is found
    private void foundID() {


        boolean search = false;



        // performing the search if the definition of the variable is not within the same line

            for (LinkedList<Token> queue : list) {

                search = ScanQUEUE(tokens.peekLast().getLexeme(), queue);



            }

            // Throw an error if the search return false
            if (!search) {
                System.out.printf("ERROR ON LINE: %d ", tokens.getFirst().getLineNum());
                System.out.println();

        }
    }





    // Searches a deque for a specific token
    private boolean ScanQUEUE(String var, LinkedList<Token> queue) {


        // using a lambda function to search the
        // since we are searching a list of deques of tokens
        // and looking for a specific string
        Optional<Token> optional = queue
                .stream()
                .filter(token -> token.getLexeme().equals("ID"))
                .findFirst();

        return optional.isPresent();

    }


    public void printT() {
        // For every queue in the list
        for (Deque<Token> queue : list) {
            // for every token in the queue
           // if (queue.getFirst().getLexeme() != null) {
                for (Token token : queue) {
                    // print the lexeme
                    //if(token.getToken()!=null) {//*******************Still possible may be where last box is coming from that or research all that make ;
                    Token t2 = token;
                    // if (t2.getLexeme() != "end")
                    System.out.print(t2.getLexeme());


                    // }
                     }

                    //if(tokens.peekFirst().getLexeme()!="end") {
                    System.out.println();

                    // }
                //}
           // }
        }
    }
}