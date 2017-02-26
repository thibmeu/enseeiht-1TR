/** Reculer le curseur d'une position.
 * @author	Xavier Crégut
 * @version	1.4
 */
public class CommandeCurseurRAZ extends CommandeLigne {

    /** Initialiser la ligne sur laquelle travaille
     * cette commande.
     * @param l la ligne
     */
    //@ requires l != null;	// la ligne doit être définie
    public CommandeCurseurRAZ(Ligne l) {
	    super(l);
    }

    public void executer() {
	    while (estExecutable) {
            ligne.reculer();
        }
    }

    public boolean estExecutable() {
	    return ligne.getCurseur() > 1;
    }

}
