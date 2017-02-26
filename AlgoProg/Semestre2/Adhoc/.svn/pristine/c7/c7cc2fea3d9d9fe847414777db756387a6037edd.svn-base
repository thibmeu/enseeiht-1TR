import java.awt.event.KeyEvent;

import javax.swing.*;

/** Classe qui enrichit le constructeur d'un JMenu.
 * Il n'est pas encore possible de faire passer efficacement
 * le raccourci clavier d'un menu dans ce constructeur.
 * Il permet d'affecter le nom et le menu englobant (JMenu ou JMenuBar via la surcharge)
 * d'un JMenu via son constructeur.
 * @author gdefranc
 */
public class CstrMenu extends JMenu {
	
public CstrMenu (String nom, JMenuBar destination) {
		super(nom);
		//primitif.setMnemonic(k.getKeyCode()); compliqué à manipuler
		destination.add(this);
	}

public CstrMenu (String nom, JMenu destination) {
		super(nom);
		destination.add(this);
		}
}
