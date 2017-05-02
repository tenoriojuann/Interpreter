/**
 * Created by I859221 on 5/1/2017.
 */

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Arrays;

import javax.print.DocFlavor;
import javax.tools.DiagnosticCollector;
import javax.tools.JavaCompiler;
import javax.tools.JavaFileObject;
import javax.tools.StandardJavaFileManager;
import javax.tools.ToolProvider;
import javax.tools.*;

public class DiagnosticCollectorCompile {

    public static void main(String args[]) throws IOException, ClassNotFoundException, IllegalAccessException, InstantiationException {
        //Interpreter in = new Interpreter(Main.class.getResource("Sample.lua").getPath());
// Compile source file.
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        compiler.run(null, null, null, (System.getProperty("user.home")+"//ex.java"));

        File root = new File(System.getProperty("user.home"));

// Load and instantiate compiled class.
        URLClassLoader classLoader = URLClassLoader.newInstance(new URL[] {root.toURI().toURL()});

        Class<?> cls = Class.forName("ex", true, classLoader);
        Object instance = cls.newInstance();

        System.out.println(instance); // Should print "ex@hashcode".
    }
}

// File: MyClass.java
class ex {
    public static void main(String args[]) {
        System.out.println("Hello, World");
    }
}

