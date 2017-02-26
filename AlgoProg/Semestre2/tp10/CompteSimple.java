/** CompteSimple modélise un compte bancaire simple tenu en euros.  Il
 * est caractérisé par un titulaire et un solde (positif ou négatif)
 * et autorise seulement les opérations de crédit et débit.
 * @author	Xavier Crégut
 * @version	1.9
 */
public class CompteSimple {

	/** Titulaire du compte. */
	private Personne titulaire;

	/** Solde du compte exprimé en euros. */
	private double solde;

	/** Initialiser un compte.
	 * @param titulaire le titulaire du compte
	 * @param depotInitial le montant initial du compte
	 */
	public CompteSimple(Personne leTitulaire, double depotInitial) throws TitulaireInvalideException, DepotInitialException{
		if (depotInitial < 0) {
            throw new DepotInitialException("Le depot initial" + depotInitial + "est inferieur a 0");
        }
        this.solde = depotInitial;

        if (leTitulaire == null) {
            throw new TitulaireInvalideException("Il faut un titulaire non null, pas comme en Suisse");
        }
		this.titulaire = leTitulaire;
	}

	/** Initialiser un compte à partir de son titulaire.
	 * Son solde est nul.
	 * @param titulaire le titulaire du compte
	 */
	public CompteSimple(Personne titulaire) throws TitulaireInvalideException, DepotInitialException {
		this(titulaire, 0);
	}

	/** Solde du compte exprimé en euros. */
	public double getSolde() {
		return this.solde;
	}

	/** Titulaire du compte. */
	public Personne getTitulaire() {
		return this.titulaire;
	}

	/** Créditer le compte du montant (exprimé en euros).
	 * @param montant montant déposé sur le compte en euros
	 */
	public void crediter(double montant) throws MontantException {
	    if (montant < 0) {
            throw new MontantException(montant, "Pas d'entreloupe");
        }
        this.solde = this.solde + montant;
	}

	/** Débiter le compte du montant (exprimé en euros).
	 * @param montant montant retiré du compte en euros
	 */
	public void debiter(double montant) throws MontantException {
		if (montant < 0) {
            throw new MontantException(montant, "Pas d'entreloupe");
        }
		this.solde = this.solde - montant;
	}

	public String toString() {
		return "solde=" + this.getSolde()
			+ ", titulaire=\"" + this.getTitulaire() + "\"";
	}

}
