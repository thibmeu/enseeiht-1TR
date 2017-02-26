import java.util.HashMap;
import java.util.Map;

public class Scores {
	
	private Map<Joueur, Integer> scores = new HashMap<Joueur, Integer>();
	
	public void ajouter(Joueur joueur, int ajout) {
		Integer ancienScore = scores.get(joueur);
		if (ancienScore == null) {
			ancienScore = 0;
		}
		scores.put(joueur, ancienScore+ajout);
	}
	
	public String scoreToString(Joueur joueur) {
		return " - " + joueur.getNom() + " : " + ((scores.get(joueur) == null) ? 0 : scores.get(joueur));
	}
	
	@Override public String toString() {
		String r = "";
		for (Joueur joueur : scores.keySet()) {
			r += scoreToString(joueur) + "\n";
		}
		return r;
	}
	
}
