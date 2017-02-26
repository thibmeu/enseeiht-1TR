


public class IdentifiantPaquet {

	private int identifiant;
	
	public IdentifiantPaquet() {
		identifiant = 0;
	}
	
	public int getNouveauIdentifiant() {
		identifiant += 1;
		return identifiant - 1;
	}
	
}
