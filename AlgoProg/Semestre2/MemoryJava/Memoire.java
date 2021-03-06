import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.Set;

public class Memoire<F, V> {
	
	private Map<F, List<Integer>> memoire = new HashMap<F, List<Integer>>();
	
	public Memoire () {
		;
	}
	
	public Memoire (Tapis<Carte<F, V>> tapis) {
		for (int iCarte = 0; iCarte < tapis.taille(); iCarte++) {
			try {
				ajouter(tapis, iCarte);
			}  catch (PositionInvalideException e) {
				System.out.println("La carte choisie possede une position invalide " + iCarte + e.getMessage());
			}
		}
	}
	
	public void ajouter(Tapis<Carte<F, V>> tapis, int iCarte) throws PositionInvalideException, OperationInvalideException{
		if (!tapis.estPrise(iCarte)) {
			boolean retournee = false;
			if (!tapis.estVisible(iCarte)) {
				tapis.montrer(iCarte);
				retournee = true;
			}
			F curFamille = (F) tapis.get(iCarte).getFamille();
			//Carte<F, V> curCarte = (Carte<F, V>) tapis.get(iCarte);
			this.ajouter(curFamille, iCarte);
			if (retournee) {
				tapis.masquer(iCarte);
			}
		}
	}
	
	public void ajouter(F curFamille, int iCarte) {
		if (!memoire.containsKey(curFamille)) {
			memoire.put(curFamille, new ArrayList<Integer>());
		}
		if (!memoire.get(curFamille).contains(new Integer(iCarte))) {
			memoire.get(curFamille).add(new Integer(iCarte));
		}
		
	}
	
	public int get(Tapis<Carte<F, V>> tapis, int iCarte, int numero) {
		try {
			return get(tapis.get(iCarte).getFamille()).get(numero);
		} catch (PositionInvalideException e) {
			throw new RuntimeException("La carte demandee n'est pas bonne");
		}
	}
	
	public List<Integer> get(F famille) {
		return memoire.get(famille);
	}
	
	public void remove(Tapis<Carte<F, V>> tapis, int iCarte) throws PositionInvalideException {
		memoire.remove(tapis.get(iCarte).getFamille());
	}
	
	public Set<F> keySet() {
		return memoire.keySet();
	}
	
	public boolean isEmpty() {
		return memoire.isEmpty();
	}
	
	public int size() {
		int curSize = 0;
		for (final List<Integer> curFamille : memoire.values()) {
			curSize += curFamille.size();
		}
		return curSize;
	}
	
	public boolean contains(int iCarte) {
		for (final List<Integer> curFamille : memoire.values()) {
			if (curFamille.contains(iCarte)) {
				return true;
			}
		}
		return false;
	}
	
}
