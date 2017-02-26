
public class AbstractJoueur implements Joueur {
	
	private String nom;
	protected Strategie strategie;
	
	protected AbstractJoueur(String nom) {
		this.nom = nom;
	}
	
	@Override
	public String getNom() {
		return nom;
	}

	@Override
	public void commencer(int tailleFamille) {
		strategie.setTailleFamille(tailleFamille);
	}

	@Override
	public int carteChoisie(int numero, Tapis<? extends Carte<?, ?>> tapis) throws OperationInvalideException {
		return strategie.carteChoisie(numero, tapis);
	}

	@Override
	public void carteRetournee(String nomJoueur, int numero, int position, Tapis<? extends Carte<?, ?>> tapis) {
		strategie.carteRetournee(nomJoueur, numero, position, tapis);
	}

	@Override
	public void cartePrise(String nomJoueur, int position, Tapis<? extends Carte<?, ?>> tapis) {
		strategie.cartePrise(nomJoueur, position, tapis);
	}

}
