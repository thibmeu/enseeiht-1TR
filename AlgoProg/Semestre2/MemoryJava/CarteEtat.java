
public class CarteEtat<C extends Carte<?,?>> {
	public static enum Etat {VISIBLE, CACHEE, RETIREE}
	
	private C carte;
	private Etat etat;
	
	public CarteEtat (C carte) {
		this(carte, Etat.CACHEE);
	}
	
	public CarteEtat (C carte, Etat etat) {
		this.carte = carte;
		this.etat = etat;
	}
	
	public C getCarte() {
		return carte;
	}
	
	public Etat getEtat() {
		return etat;
	}
	
	public void setEtat(Etat etat) {
		this.etat = etat;
	}
	
}
