import com.google.gson.JsonObject;
import java.util.Stack;
import java.util.ArrayList;
public class Parser {



    public Parser(){
    //create what is going to be needed:
    //Stack will check to see if execption is thrown.
        Stack<String> exceptionCheck = new Stack<String>();
    //Array list that will take in tokens. Array list makes it easy to recover if there is an exception thrown.
    //Vector will be used if we make it in C++. 
        ArrayList<Tokens> tokens= new ArrayList<>();//might be treated as tree
        
   //Method that uses Scanner to take in tokens and see if exception is thrown. 
        //counter with while loop
        int counter=0;
        //not sure if this works may have 
        while (counter<tokens.length){
            //go back and fill tokens arrayList
            
        }
        /*error to check for: 
        What is final token?
        KW: int, if, while, end
        letter, digit, =, <=, <, >=,>, ==, ~=, +, -, *, /, (, )
        Reading over language may need to include following.
        Make sure reserved words are used: and, break, do, else, elseif, end, 
                False, for, function, if, in, local, nil, not, or, repeat, return, 
                then, true, until, while.
        Possible: {,},[,], ;, :, ., .. , ...
        */
        //Run through loop if token is one of the viable tokens run a functions for 
        if(tokens[counter].lexeme=="("){
            counter2=counter;
            LP_Present();
            if(!goOn){
                break;}
            //put in tree
            
        }        
    }
    public static void LP_Present[]{
        this.counter2++;
        if(token[counter2]=")"){
            this.goOn=true;
            break;
        }
        if (counter2+1<token.size){
            LP_Present();
        }
        else{//end as well if end or semicolon is hit
            goOn=false;
            System.out.print("Right parenthesis not present at row: " +token[counter].row + " column: " +token[counter].column);
            break;
        }
           


}
