
public interface Strategie {
	
	int carteChoisie(int numero, Tapis<? extends Carte<?, ?>> tapis) throws OperationInvalideException;
	
	void carteRetournee(String nomJoueur, int numero, int position, Tapis<? extends Carte<?, ?>> tapis);
	
	void cartePrise(String nomJoueur, int position, Tapis<? extends Carte<?, ?>> tapis);
	
	String toString();
	
	void setTailleFamille(int tailleFamille);
	
}
