import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.io.*;
import java.net.*;

public class MediaRemote extends JFrame {

    //Graphical UI components
    private static final long serialVersionUID = 1L;
    private final Dimension WINDOW_SIZE = new Dimension(600, 400);
    private JTextArea mainTextArea;
    private JMenuBar menubar;
    private JMenu mainMenu;
    private JToolBar toolbar;
    private Action addAction1;
    private Action addAction2;
    private Action exitAction;

    //Client components
    static final String DEFAULT_HOST = "localhost";
    static final int DEFAULT_PORT = 3334;
    private Socket sock;
    private BufferedReader input;
    private BufferedWriter output;

    public static void main(String argv[]) {
        String host = DEFAULT_HOST;
        int port = DEFAULT_PORT;
        if (argv.length >=1) host = argv[0];
        if (argv.length >=2) port = Integer.parseInt(argv[1]);
        
        MediaRemote client = null;
        
        try {
            client = new MediaRemote(host, port);
        }
        catch (Exception e) {
            System.err.println("Client: Couldn't connect to "+host+":"+port);
            System.exit(1);
        }
        
        System.out.println("Client connected to "+host+":"+port);

        // Read from console
        BufferedReader cin = new BufferedReader(new InputStreamReader(System.in));
        
        while (true) {
            System.out.print("Request: ");
            try {
                String request = cin.readLine();
                String response = client.send(request);
                System.out.println("Response: " + response);
            }
            catch (java.io.IOException e) {
                System.err.println("Client: IO error");
                return;
            }
        }
    }

    public MediaRemote(String host, int port) throws UnknownHostException, IOException {
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        /////////////////////////////UI SETUP/////////////////////////////
        //We add at the center of the frame a JTextArea
        mainTextArea = new JTextArea(5, 20);
        //We give the mainTextArea a scrollPane
        JScrollPane scrollPane = new JScrollPane(mainTextArea);
        add(scrollPane, "Center");

        //We define the actions
        addAction1 = new AddTextAction("Button 1", "Button 1 was pressed\n");
        addAction2 = new AddTextAction("Button 2", "Button 2 was pressed\n");
        exitAction = new AbstractAction("Exit") {
           @Override 
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        };

        //We add three buttons inside a JPanel south of the frame
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(new JButton(addAction1));
        buttonPanel.add(new JButton(addAction2));
        buttonPanel.add(new JButton(exitAction));
        add(buttonPanel, "South");

        //We add the menu bar in the frame with a menu
        mainMenu = new JMenu("File");
        menubar = new JMenuBar();
        menubar.add(mainMenu);
        mainMenu.add(addAction1);
        mainMenu.add(addAction2);
        mainMenu.addSeparator();
        mainMenu.add(exitAction);
        setJMenuBar(menubar);

        //We add the toolbar in the frame with the same buttons as the JPanel
        toolbar = new JToolBar();
        toolbar.add(addAction1);
        toolbar.add(addAction2);
        toolbar.addSeparator();
        toolbar.add(exitAction);
        add(toolbar, "North");


        //We set the minimum and maximum size of the frame
        setPreferredSize(WINDOW_SIZE);
        pack();
        setVisible(true);
        /////////////////////////////END OF UI SETUP/////////////////////////////

        try{
            sock = new java.net.Socket(host, port);
        } catch(java.net.UnknownHostException e) {
            System.err.println("Client: Couldn't find host "+host+":"+port);
            mainTextArea.append("Client: Couldn't find host "+host+":"+port + "\n");
            throw e;
        } catch(java.io.IOException e) {
            System.err.println("Client: Couldn't reach host "+host+":"+port);
            mainTextArea.append("Client: Couldn't reach host "+host+":"+port + "\n");
            throw e;
        }

        try {
            input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
        } catch (java.io.IOException e) {
            System.err.println("Client: Couldn't open input or output streams");
            throw e;
        }   
        
    }

    public String send(String request) {
        // Send request to server
        try {
          request += "\n";  // line terminator
          output.write(request, 0, request.length());
          output.flush();
        }
        catch (java.io.IOException e) {
          System.err.println("Client: Couldn't send message: " + e);
          return null;
        }
        
        // Get result sent by server
        try {
          return input.readLine();
        }
        catch (java.io.IOException e) {
          System.err.println("Client: Couldn't receive message: " + e);
          return null;
        }
    }

    class AddTextAction extends AbstractAction {
        private String textToAdd;

        public AddTextAction(String name, String text) {
            super(name);
            this.textToAdd = text;
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            mainTextArea.append(textToAdd);
        }
    }
}
