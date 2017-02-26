import java.util.Observable;
import java.util.Observer;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ChatSwing extends JFrame implements Observer {
    
    private static Chat chat = new Chat("ChatSwing");
    private String pseudo = "XXX";
    private JButton fermer = new JButton("Fermer");
    private JTextArea textMessages = new JTextArea();
    private JPanel utilBas = new JPanel();
    private JLabel zoneNom = new JLabel(pseudo);
    private JTextField zoneSaisie = new JTextField();
    private JButton buttonOk = new JButton("OK");

    public ChatSwing() {
        super();
        this.setLayout(new GridLayout(3, 1));
        this.add(fermer);
        this.add(textMessages);
        this.add(utilBas);
        utilBas.setLayout(new BorderLayout());
        utilBas.add(zoneNom);
        utilBas.add(zoneSaisie);
        utilBas.add(buttonOk);

        this.pack();
        this.setVisible(true);
    }

    public void update(Observable o, Object arg) {
        System.out.println(((Chat)o).getNom() + "> " + (String)arg);
    }
    
    public class ActionOk implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            chat.ajouter(new MessageTexte(pseudo, zoneSaisie.getText()));
            zoneSaisie.setText("");
        }
    }

    public static void main(String[] argc)
}
