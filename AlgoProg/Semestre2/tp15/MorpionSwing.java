import javax.swing.*;
import java.awt.*;
import javax.swing.event.*;
import java.awt.event.*;
import java.util.*;

/** Programmation d'un jeu de Morpion avec une interface graphique Swing.
  *
  * REMARQUE : Dans cette solution, le patron MVC n'a pas été appliqué !
  * On a un modèle (?), une vue et un contrôleur qui sont fortement liés.
  *
  * @author	Xavier Crégut
  * @version	$Revision: 1.4 $
  */

public class MorpionSwing {

	// les images à utiliser en fonction de l'état du jeu.
	private static final Map<ModeleMorpion.Etat, ImageIcon> images
		= new HashMap<ModeleMorpion.Etat, ImageIcon>();
	static {
		images.put(ModeleMorpion.Etat.VIDE, new ImageIcon("blanc.jpg"));
		images.put(ModeleMorpion.Etat.CROIX, new ImageIcon("croix.jpg"));
		images.put(ModeleMorpion.Etat.ROND, new ImageIcon("rond.jpg"));
	}
    
    private class ActionQuitter implements ActionListener {
        @Override public void actionPerformed(ActionEvent e) {
            quitter();
        }
    }
    
    private class ActionNouvellePartie implements ActionListener {
        @Override public void actionPerformed(ActionEvent e) {
            recommencer();
        }
    }
    
    private class ActionCocher extends MouseAdapter {
        int i, j;
        public ActionCocher(int i, int j) {
            this.i = i;
            this.j = j;
        }

        @Override public void mouseClicked(MouseEvent e) {
            cocher(i, j);
        }
    }

// Choix de réalisation :
// ----------------------
//
//  Les attributs correspondant à la structure fixe de l'IHM sont définis
//	« final static » pour montrer que leur valeur ne pourra pas changer au
//	cours de l'exécution.  Ils sont donc initialisés sans attendre
//  l'exécution du constructeur !

	private ModeleMorpion modele;	// le modèle du jeu de Morpion

//  Les éléments de la vue (IHM)
//  ----------------------------

	/** Fenêtre principale */
	private JFrame fenetre;

	/** Bouton pour quitter */
	private final JButton boutonQuitter = new JButton("Q");

	/** Bouton pour commencer une nouvelle partie */
	private final JButton boutonNouvellePartie = new JButton("N");

	/** Cases du jeu */
	private final JLabel[][] cases = new JLabel[3][3];

	/** Zone qui indique le joueur qui doit jouer */
	private final JLabel joueur = new JLabel();


// Le constructeur
// ---------------

	/** Construire le jeu de morpion */
	public MorpionSwing() {
		this(new ModeleMorpionSimple());
	}

	/** Construire le jeu de morpion */
	public MorpionSwing(ModeleMorpion modele) {
		// Initialiser le modèle
		this.modele = modele;

		// Créer les cases du Morpion
		for (int i = 0; i < this.cases.length; i++) {
			for (int j = 0; j < this.cases[i].length; j++) {
				this.cases[i][j] = new JLabel();
			}
		}

		// Initialiser le jeu
		this.recommencer();

		// Construire la vue (présentation)
		//	Définir la fenêtre principale
		this.fenetre = new JFrame("Morpion");
		this.fenetre.setLocation(100, 200);

        // On ajoute les elements
        Container contenu = fenetre.getContentPane();
        contenu.setLayout(new GridLayout(4, 3));
        for (int i = 0; i < cases.length; i++) {
            for (int j = 0; j < cases.length; j++) {
                cases[i][j].addMouseListener(new ActionCocher(i, j));
                contenu.add(cases[i][j]);
            }
        }

        boutonNouvellePartie.addActionListener(new ActionNouvellePartie());
        contenu.add(boutonNouvellePartie);
        contenu.add(joueur);
        boutonQuitter.addActionListener(new ActionQuitter());
        contenu.add(boutonQuitter);

        JMenu menu = new JMenu("Jeu");
        menu.add("Nouvelle partie");
        menu.add("Quitter");
        JMenuBar menuBar = new JMenuBar();
        menuBar.add(menu);
        
        fenetre.setJMenuBar(menuBar);

		// Construire le contrôleur (gestion des événements)
		this.fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// afficher la fenêtre
		this.fenetre.pack();			// redimmensionner la fenêtre
		this.fenetre.setVisible(true);	// l'afficher
	}

// Quelques réactions aux interactions de l'utilisateur
// ----------------------------------------------------

	/** Recommencer une nouvelle partie. */
	public void recommencer() {
		this.modele.recommencer();

		// Vider les cases
		for (int i = 0; i < this.cases.length; i++) {
			for (int j = 0; j < this.cases[i].length; j++) {
				this.cases[i][j].setIcon(images.get(this.modele.getValeur(i, j)));
			}
		}

		// Mettre à jour le joueur
		joueur.setIcon(images.get(modele.getJoueur()));
	}

    public void quitter() {
        System.out.println("Fin");
        fenetre.dispose();
    }
    
    public void cocher(int i, int j) {
        if (modele.estGagnee()) {
            recommencer();
        }

        try {
            modele.cocher(i, j);
            cases[i][j].setIcon(images.get(modele.getJoueur()));
            if (modele.getJoueur() == ModeleMorpion.Etat.CROIX) {
                joueur.setIcon(images.get(ModeleMorpion.Etat.ROND));
            } else {
                joueur.setIcon(images.get(ModeleMorpion.Etat.CROIX));
            }
        } catch (CaseOccupeeException e) {
            return;
        }
    }

// La méthode principale
// ---------------------

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				new MorpionSwing();
			}
		});
	}

}
