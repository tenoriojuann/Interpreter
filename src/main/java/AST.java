import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

/**
 * Created by I859979 on 2/13/2017.
 */
public class AST {




    JsonObject program = new JsonObject();


    // Sets the initial properties that every program will have
    public AST(){
        program.addProperty("type", "program");
        program.add("program", new JsonArray());
    }


    // Adds new entries to the program, per line
    public void setObject(JsonObject object){

        program.getAsJsonArray("program").add(object);
    }
}
