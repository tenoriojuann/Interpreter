import java.io.IOException;
import java.util.*;

public class ParserV2 {


    private LinkedList<Token> tokens = new LinkedList();
    private LinkedList<LinkedList<Token>> list = new LinkedList();
    private String filename;
    public String pLast;

    public ParserV2(String filename) {
        this.filename = filename;
    }

    public void populateList() throws IOException {

        Lexer lex = new Lexer(filename);
        Token tok = lex.nextToken();
        tokens.addLast(tok);
        //keeps track of line number for tokens, when next token linenumber > counter adds current linked list token
        //to list and then makes new linked list token for next line.
        //Tokens are (type, lexeme, line number)
        int counter = 1;
        while (lex.fp.ready()) {
            if (tok.getLineNum() == counter) {
                tokens.addLast(tok);
            }


            if(tok.getLineNum()>counter){
                counter++;
                list.addLast(new LinkedList<>(tokens));
                tokens.clear();
                tokens.addLast(tok);
            }
            tok=lex.nextToken();
        }
        lex.fp.close();
        }


    public void printT(){
        int counter=0;
        while (list.size()<counter){
            int counter2=0;
            while(counter2<list.get(counter).size()) {
                System.out.print(list.get(counter).get(counter2).getLexeme() + " ");
                counter2++;
            }
            counter++;
            System.out.println();
        }

    }
    public void printErrors(){
        int counter=0;
        while (list.size()<counter){
            int counter2=0;
            System.out.print(list.get(counter).get(counter2).getLexeme() + " ");

            counter2++;
        }
        System.out.println();
        counter++;
    }
}