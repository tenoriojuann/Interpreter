import com.google.gson.JsonObject;

public class Parser {



    public Parser(){


    }

    // This will work for the int case
    // But we'll need to re-write it for more complex things
    public JsonObject varType(String type, String value){
        JsonObject typeJ = new JsonObject();
        typeJ.addProperty(type, value);

        return typeJ;
    }

}
