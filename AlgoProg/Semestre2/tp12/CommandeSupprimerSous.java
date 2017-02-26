/** Reculer le curseur d'une position.
 * @author	Xavier Crégut
 * @version	1.4
 */
public class CommandeSupprimerSous extends CommandeLigne {

    /** Initialiser la ligne sur laquelle travaille
     * cette commande.
     * @param l la ligne
     */
    //@ requires l != null;	// la ligne doit être définie
    public CommandeSupprimerSous(Ligne l) {
	    super(l);
    }

    public void executer() {
	    ligne.supprimer();
    }

    public boolean estExecutable() {
	    return ligne.getLongeur() > 0;
    }

}
