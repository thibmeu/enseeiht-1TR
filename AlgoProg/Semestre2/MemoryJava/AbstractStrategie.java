import java.util.Iterator;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;

public abstract class AbstractStrategie implements Strategie {
	
	protected int tailleFamille;
	protected Memoire memoire = new Memoire();
	
	public abstract int carteChoisie(int numero, Tapis<? extends Carte<?, ?>> tapis) throws OperationInvalideException;
	
	public void carteRetournee(String nomJoueur, int numero, int position, Tapis<? extends Carte<?, ?>> tapis) {
		try {
			memoire.ajouter(tapis, position);
		} catch (PositionInvalideException e) {
			e.printStackTrace();
		}
	}
	
	public void cartePrise(String nomJoueur, int position, Tapis<? extends Carte<?, ?>> tapis) {
		try {
			memoire.remove(tapis, position);
		} catch (PositionInvalideException e) {
			e.printStackTrace();
		}
	}
	
	protected List<Integer> familleComplete() {
		if (memoire.isEmpty()) {
			return null;
		}
		Set<?> famillesMemorisees = memoire.keySet();
		Iterator<?> iFamille = famillesMemorisees.iterator();
		List<Integer> famille = memoire.get(iFamille.next());
		while (iFamille.hasNext()) {
			List <Integer> curFamille = memoire.get(iFamille.next());
			if (curFamille.size() > famille.size()) {
				famille = curFamille;
			}
		}
		
		return (famille.size() == tailleFamille) ? famille : null;
	}
	
	protected int choixExpert(Tapis<? extends Carte<?, ?>> tapis) {
		List<Integer> famille = familleComplete();
		if (famille != null) {
			for (final int iCarte : famille) {
				boolean visible = true;
				try {
					visible = tapis.estVisible(iCarte);
				} catch (PositionInvalideException e) {
					e.printStackTrace();
				}
				if (!visible) {
					return iCarte;
				}
			}
		}
		
		return choixHasard(tapis, true);
	}
	
	private int choixHasard(Tapis<? extends Carte<?, ?>> tapis, boolean useYourMind) {
		int iCarteChoisie = 0;
		Random rd = new Random();
		boolean ok = true;
		do {
			iCarteChoisie = rd.nextInt(tapis.taille());
			//A SUPPRIMER !!!!!
			System.out.println("" + tapis.taille() + "-" + tapis.nbCartesRestantes() + "-" + memoire.size() + "-");
			try {
				System.out.println(iCarteChoisie);
				ok = tapis.estPrise(iCarteChoisie) || tapis.estVisible(iCarteChoisie);
				if (useYourMind && memoire.contains(iCarteChoisie)) {
					ok = true;
				}
			} catch (PositionInvalideException e) {
				System.out.println("La carte choisie n'est pas a la bonne position " + iCarteChoisie + e.getMessage());
			} catch (CartePriseException e) {
				;
			}
		} while (ok);
		return iCarteChoisie;
	}
	
	protected int choixHasard(Tapis<? extends Carte<?, ?>> tapis) {
		return choixHasard(tapis, false);
	}
	
	public void setTailleFamille(int tailleFamille) {
		if (tailleFamille > 0) {
			this.tailleFamille = tailleFamille;
		} else {
			throw new NumberFormatException("La taille de famille doit etre superieure ou egale a 0");
		}
	}
	
}
