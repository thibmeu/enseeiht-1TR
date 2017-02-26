/** Ajouter un caractère à la fin de la ligne.
 * @author	Xavier Crégut
 * @version	1.4
 */
public class SousMenu extends Menu implements Commande {

    /** Initialiser la ligne sur laquelle travaille
     * cette commande.
     * @param l la ligne
     */
    //@ requires l != null;	// la ligne doit être définie
    public SousMenu(String sonTitre) {
	    super(sonTitre);
    }

    public void executer() {
	    this.afficher();
    }

    public boolean estExecutable() {
	    return getNbEntrees() > 0;
    }

}
