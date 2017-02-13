import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

/**
 * Created by I859979 on 2/13/2017.
 */
public class Import {

    String src;
    Import(String url) throws IOException {

        newFile(url);

    }

    public void newFile(String url) throws IOException {
        src =  new String(Files.readAllBytes(Paths.get(url)), "UTF-8");
    }

}
