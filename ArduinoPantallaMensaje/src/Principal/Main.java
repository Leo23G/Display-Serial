package Principal;

import gnu.io.*;
import java.util.Enumeration;
import Interface.Ventana;

public class Main {
    public static void main(String erg[])
    {
        CommPortIdentifier port;
        Enumeration<?> puerto = CommPortIdentifier.getPortIdentifiers();
        System.out.println(puerto.hasMoreElements());
        while(puerto.hasMoreElements())
        {
            port = (CommPortIdentifier) puerto.nextElement();
            System.out.println("Puerto "+port.getName());
        }
        
        
        Ventana ventana = new Ventana();

    }
}
