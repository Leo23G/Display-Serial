package Interface;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Enumeration;
 
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import static java.awt.image.ImageObserver.ERROR;
 
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
 
public final class Ventana extends JFrame
{
    private OutputStream Output = null;
    SerialPort serialPort;
    private final String PORT_NAME = "COM3";
    private static final int TIME_OUT = 2000;
    private static final int DATA_RATE = 9600;
    private final JButton btnEnviarTexto,btnCerrar;
    private static JTextField txtMensaje;
    private final JLabel labelTitle;
 
    public Ventana()
    {
        btnEnviarTexto = new JButton("Enviar");
        txtMensaje = new JTextField();
        btnCerrar = new JButton("Cerrar");
        labelTitle = new JLabel("Inserte su mensaje aqui");
        initializeArduinoConnection();
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(350,250);
        this.setUndecorated(true);
        this.setVisible(true);
        this.setLocationRelativeTo(null);
        this.setLayout(null);
        this.add(btnEnviarTexto);
        this.add(txtMensaje);
        this.add(btnCerrar);
        this.add(labelTitle);
        labelTitle.setBounds(30,20,250,20);
        txtMensaje.setBounds(50,50,250,30);
        btnEnviarTexto.setBounds(110, 110, 100, 30);
        btnCerrar.setBounds(110, 150, 100, 30);
        Escuchas();
    }

    public void initializeArduinoConnection()
    {
        CommPortIdentifier portId = null;
        Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

        while (portEnum.hasMoreElements()) 
        {
            CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();
            if (PORT_NAME.equals(currPortId.getName())) 
            {
                portId = currPortId;
                break;
            }
        }

        if (portId == null) 
        {
            showError(PORT_NAME);
            System.exit(ERROR);
            return;
        }

        try 
        {
            serialPort = (SerialPort) portId.open(this.getClass().getName(), TIME_OUT);
            serialPort.setSerialPortParams(DATA_RATE,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);
            Output = serialPort.getOutputStream();

        } catch (Exception e) {
            System.exit(ERROR);
        }
    }

    private void showError(String errorMessage){
            JOptionPane.showMessageDialog(null,errorMessage,"Error",JOptionPane.ERROR_MESSAGE);
    }

    private void Escuchas(){
        
        btnEnviarTexto.addMouseListener(new MouseAdapter()
        {
            public void mouseClicked(MouseEvent ev)
            {
                String data = txtMensaje.getText();
                txtMensaje.setText(null);
                try 
                {
                    Output.write(data.getBytes());
                } 
                catch (IOException ex) 
                {
                    System.exit(ERROR);
                }
            }
        });
        
        txtMensaje.addKeyListener(new KeyAdapter()
        {

            public void keyTyped(KeyEvent e)
            {
                if (txtMensaje.getText().length()== 25)
                e.consume();
            }
            
            public void keyReleased(KeyEvent e) 
            {
                if(e.getKeyCode()==e.VK_ENTER)
                {
                    String data = txtMensaje.getText();
                    txtMensaje.setText(null);
                    try 
                    {
                        Output.write(data.getBytes());
                    } 
                    catch (IOException ex) 
                    {
                        System.exit(ERROR);
                    }
                }
            }
        });
        
        btnCerrar.addMouseListener(new MouseAdapter()
        {
            public void mouseClicked(MouseEvent ev){
                System.exit(0);
            }
        });
    }
}