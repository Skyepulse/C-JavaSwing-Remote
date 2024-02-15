import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingUtilities;

public class MediaRemote implements Runnable {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new MediaRemote());
    }

    @Override
    public void run() {
        JFrame frame = new JFrame("Simple Swing Example");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JLabel label = new JLabel("Hello, Swing!");
        frame.add(label);
        frame.pack();
        frame.setVisible(true);
    }
}
