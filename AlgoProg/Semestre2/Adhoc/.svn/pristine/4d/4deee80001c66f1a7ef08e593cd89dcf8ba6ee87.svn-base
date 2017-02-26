import java.awt.EventQueue;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import java.awt.BorderLayout;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JPanel;
import javax.swing.JTextPane;

import java.awt.CardLayout;

/** La classe fenetre represente l'interface graphique du projet.
 * Elle a pour attribut une JFrame.
 * Elle contient un constructeur (qui appelle la fonction initialize)
 * ainsi qu'un main qui lance la fenetre.
 * @author gdefranc
 */
public class Fenetre {
	
	private JFrame frame;
	
	// lancer l'application
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Fenetre window = new Fenetre();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	// creer l'application
	public Fenetre() {
		initialize();
	}


	

/** La fonction initialize est celle qui definit le fonctionnement de la fenetre.
 * Apres avoir declare et instancie tous les menus et autres objets graphiques,
 * on definit le layout pour pouvoir definir le contenu du menu (changer de sous menu).
 * On a une classe interne qui represente l'ecouteur utilise pour naviguer dans le menu 
 * contextuel a l'aide de la souris. Javadoc de l'ecouteur (classe interne) non generee : on pourrait
 * sortir cette classe et la mettre dans son propre fichier.
 */
// Constructeur de la fenêtre
private void initialize () {
	// Attributs menus
 JMenuBar menuBar = new JMenuBar();
 JMenu menu0 = new JMenu("Paquet");
 JMenuItem menuItem01= new JMenuItem("Ajouter");
 JMenuItem menuItem02 = new JMenuItem("Supprimer");
 JMenuItem menuItem03 = new JMenuItem("Activer/Desactiver");

JMenu menu1 = new JMenu("Noeud");
JMenuItem menuItem11 = new JMenuItem("Expediteur");
JMenuItem menuItem12 = new JMenuItem("Contenu");
JMenuItem menuItem13 = new JMenuItem("Destinataire");

frame = new JFrame("Interface Graphique");
frame.setBounds(100, 100, 450, 300);
frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

// Carte en mode BorderLayout (points cardinaux) :
/*JTextPane txtpnCarte = new JTextPane();
txtpnCarte.setText("Carte");
frame.getContentPane().add(txtpnCarte, BorderLayout.SOUTH);*/

//Carte en mode AbsoluteLayout (postionnement au pixel pres) :
JTextPane txtpnCarte = new JTextPane();
txtpnCarte.setBounds(20, 20, 200, 21);
txtpnCarte.setText("Carte");
frame.getContentPane().add(txtpnCarte);

CardLayout cardL = new CardLayout();
JPanel content = new JPanel();


// ajout des menus dans l'ordre
menuBar.add(menu0);
menuBar.add(menu1);

// ajout de notre listener sur les menus/ sous menus
// code infame, a factoriser

//Classe AccederSuivant : Action Listener qui permet de se deplacer dans un menu contextuel

	/** La classe AccederSuivant implemente ActionListener.
	 * Elle redefinit la fonction actionPerformed :
	 * on passe au contenu suivant du layout lors d'un clic (navigation
	 * dans le menu contextuel).
	 * @author gdefranc
	 */
	 class AccederSuivant implements ActionListener{
			
		@Override
		public void actionPerformed (ActionEvent e) {
			cardL.next(content); 
		}
}

// On ajoute l'action listener AccederSuivant sur tous les menus
menu0.addActionListener(new AccederSuivant());

menu1.addActionListener(new AccederSuivant());


// Il faudrait ajouter ce Listener a tous les sous menus (menu Item)
menuItem11.addActionListener(new AccederSuivant());
menuItem02.addActionListener(new AccederSuivant());
			
// ajout de notre sous menu
menu0.add(menuItem01);
menu0.add(menuItem02);
menu0.add(menuItem03);
menu1.add(menuItem11);
menu1.add(menuItem12);
menu1.add(menuItem13);

// ajout du MenuBar
frame.setJMenuBar(menuBar);

// definition du layout
content.setLayout(cardL);
frame.getContentPane().add(content, BorderLayout.CENTER);

}

}
