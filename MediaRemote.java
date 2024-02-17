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
    private Action instructionsAction;

    private JTextField inputField;
    private Action searchAction;
    private Action playAction;
    private Action displayInfoAction;
    private Action deleteMediaAction;
    private Action deleteGroupAction;
    private Action saveAction;
    private Action loadAction;

    //Miscellaneous
    private final String NEW_REQUEST_LINE = "//////////////////////////NEW REQUEST/////////////////////////\n";
    private final String INSTRUCTIONS = """
            ////////////////////////////INSTRUCTIONS/////////////////////////
            Welcome to the MediaRemote application. This application allows you to interact with a media server.
            You can use the buttons to send requests to the server, and receive the response in the text area.
            The instructions for the buttons are as follows: \n
            - Search: Searches for available media that have the given text in their name. If empty, returns all media. \n
            - Play: Plays the media with the given name. Please be aware that the name must be exact. \n
            - Display Media Info: Displays the information of the media with the given name. \n
            - Delete Media: Deletes the media with the given name. CAREFUL: if a media is deleted before the database is saved,
            it will be lost forever. \n
            - Delete Group: Deletes the group with the given name. Same warning as the Delete Media button. \n
            - Save: Saves the current state of the database. \n
            - Load: Loads the last saved state of the database. \n
            ////////////////////////////END OF INSTRUCTIONS////////////////////\n
            """;

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
        addAction1 = new AddTextAction("Add space", "\n");
        addAction2 = new AbstractAction("Reset Text Area"){
           @Override 
            public void actionPerformed(ActionEvent e) {
                mainTextArea.setText("");
            } 
        };
        exitAction = new AbstractAction("Exit") {
           @Override 
            public void actionPerformed(ActionEvent e) {
                //We open a dialog box to confirm the exit
                int response = JOptionPane.showConfirmDialog(null, "Are you sure you want to exit?", "Exit", JOptionPane.YES_NO_OPTION);
                if (response == JOptionPane.YES_OPTION)
                     System.exit(0);
            }
        };
        instructionsAction = new AddTextAction("Instructions", INSTRUCTIONS);

        //We define the actions for the other buttons
        searchAction = new SendServerAction("Search For Media", "search");
        playAction = new SendServerAction("Play Media", "play");
        displayInfoAction = new SendServerAction("Display Media Info", "find");
        deleteMediaAction = new SendServerActionDialogBox("Delete Media", "destroyMedia", "Enter the name of the media you are CERTAIN you wish to delete: ");
        deleteGroupAction = new SendServerActionDialogBox("Delete Group", "destroyGroup", "Enter the name of the group you are CERTAIN you wish to delete: ");
        saveAction = new SendServerSimpleMessage("Save", "save");
        loadAction = new SendServerSimpleMessage("Load", "readSave");

        //We first instanciate a JPanel with a BorderLayout
        JPanel rightPanel = new JPanel(new BorderLayout(5, 5));
        //We add a JPanel containing a vertical layout with a label and the textField at the north of the panel
        JPanel inputPanel = new JPanel(new GridLayout(2, 1, 5, 5));
        inputPanel.add(new JLabel("Enter the desired request addition:"));
        inputField = new JTextField();
        inputPanel.add(inputField);
        rightPanel.add(inputPanel, "North");
        //Now we add a JPanel with a 2X3 GridLayout containing the buttons
        JPanel requestsPanel = new JPanel(new GridLayout(3, 2, 5, 5));
        requestsPanel.add(new JButton(searchAction));
        requestsPanel.add(new JButton(displayInfoAction));
        JButton deleteMediaButton = new JButton(deleteMediaAction);
        deleteMediaButton.setBackground(Color.RED);
        JButton deleteGroupButton = new JButton(deleteGroupAction);
        deleteGroupButton.setBackground(Color.RED);
        requestsPanel.add(deleteMediaButton);
        requestsPanel.add(deleteGroupButton);
        requestsPanel.add(new JButton(saveAction));
        requestsPanel.add(new JButton(loadAction));
        rightPanel.add(requestsPanel, "Center");
        //Finally we add the play button at the south of the panel
        rightPanel.add(new JButton(playAction), "South");
        add(rightPanel, "East");


        

        

        //We add three buttons inside a JPanel south of the frame
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(new JButton(addAction1));
        buttonPanel.add(new JButton(addAction2));
        buttonPanel.add(new JButton(instructionsAction));
        buttonPanel.add(new JButton(exitAction));
        add(buttonPanel, "South");

        //We add the menu bar in the frame with a menu
        mainMenu = new JMenu("File");
        menubar = new JMenuBar();
        menubar.add(mainMenu);
        mainMenu.add(addAction1);
        mainMenu.add(addAction2);
        mainMenu.add(instructionsAction);
        mainMenu.addSeparator();
        mainMenu.add(exitAction);
        setJMenuBar(menubar);

        //We add the toolbar in the frame with the same buttons as the JPanel
        toolbar = new JToolBar();
        toolbar.add(addAction1);
        toolbar.add(addAction2);
        toolbar.add(instructionsAction);
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

    class SendServerAction extends AbstractAction{
        private String actionText;

        public SendServerAction(String name, String text){
            super(name);
            this.actionText = text;
        }

       @Override
        public void actionPerformed(ActionEvent e) {
            String mainString = actionText + " " + inputField.getText();
            mainTextArea.append(NEW_REQUEST_LINE);
            mainTextArea.append("REQUEST: " + mainString + "\n");
            String response = send(mainString);
            mainTextArea.append("RESPONSE: " + response + "\n");
        } 
    }

    class SendServerActionDialogBox extends AbstractAction{
        private String actionText;
        private String dialogText;

        public SendServerActionDialogBox(String name, String text, String dialogText){
            super(name);
            this.actionText = text;
            this.dialogText = dialogText;
        }

       @Override
        public void actionPerformed(ActionEvent e) {
            String mainString = JOptionPane.showInputDialog(dialogText);
            if (mainString == null) return;
            mainString = actionText + " " + mainString;
            mainTextArea.append(NEW_REQUEST_LINE);
            mainTextArea.append("REQUEST: " + mainString + "\n");
            String response = send(mainString);
            mainTextArea.append("RESPONSE: " + response + "\n");
        } 
    }

    class SendServerSimpleMessage extends AbstractAction{
        private String actionText;

        public SendServerSimpleMessage(String name, String text){
            super(name);
            this.actionText = text;
        }

       @Override
        public void actionPerformed(ActionEvent e) {
            String mainString = actionText;
            mainTextArea.append(NEW_REQUEST_LINE);
            mainTextArea.append("REQUEST: " + mainString + "\n");
            String response = send(mainString);
            mainTextArea.append("RESPONSE: " + response + "\n");
        } 
    }
}
