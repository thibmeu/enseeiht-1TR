import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/** La classe Arbitre permet de gérer une partie de Memory
  * entre plusieurs jourueurs.
  *
  * @author	Xavier Crégut <Prenom.Nom@enseeiht.fr>
  */
public class Arbitre {
	
	List<Joueur> joueurs = new ArrayList<Joueur>();
	Scores scores = new Scores();
	AfficheurTapis afficheur;
	
	public Arbitre(AfficheurTapis afficheur) {
		this.afficheur = afficheur;
	}
	
	/** Inscrire un joueur.
	 * @param joueur le joueur à inscrire
	 */
	public void inscrire(Joueur joueur) {
		joueurs.add(joueur);
		scores.ajouter(joueur, 0);
	}
	
	private <F, V> int demandeEntree(Joueur joueur, Tapis<Carte <F, V>> tapis, Tapis<Carte <F, V>> tapisReel, int iCarte) {
		int iCarteChoisie = 0;
		try {
			iCarteChoisie = joueur.carteChoisie(iCarte, tapis);
			if (tapisReel.estVisible(iCarteChoisie)){
				System.out.println("La carte " + iCarteChoisie + " est déjà visible." + joueur.getNom());
				return iCarteChoisie;
			}
		} catch (PositionInvalideException e) {
			System.out.println("La position " + iCarteChoisie + "est invalide");
		} catch (CartePriseException e) {
			System.out.println("La carte " + iCarteChoisie + " est déà prise.");
		}
		
		return iCarteChoisie;
	}
	
	private <F, V> boolean isFamille(Tapis<Carte <F, V>> tapisReel, List<Integer> cartes) {
		try {
			F curFamille = tapisReel.get(cartes.get(0)).getFamille();
			for (int iCarte : cartes) {
				if (tapisReel.get(iCarte).getFamille() != curFamille) {
					return false;
				}
			}
		} catch (PositionInvalideException e) {
			System.out.println("La position " + cartes.get(0) + " est invalide");
			return false;
		}
		
		return true;
	}
	
	private <F, V> void infoRetournee (Joueur joueur, Tapis<Carte <F, V>> tapis, Tapis<Carte <F, V>> tapisReel, int iCarte, int iCarteChoisie) {
		for (final Joueur curJoueur : joueurs) {
			//if (curJoueur != joueur) {
				curJoueur.carteRetournee(joueur.getNom(), iCarte, iCarteChoisie, tapis);
			//}
		}
	}
	
	private <F, V> void infoPrise (Joueur joueur, Tapis<Carte <F, V>> tapis, Tapis<Carte <F, V>> tapisReel, List<Integer> cartesChoisies) {
		for (final int iCarte : cartesChoisies) {
			try {
				for (final Joueur curJoueur : joueurs) {
					curJoueur.cartePrise(joueur.getNom(), iCarte, tapis);
				}
				tapisReel.prendre(iCarte);
			} catch (PositionInvalideException e) {
				System.out.println("Dammed! Encore rate!");
			}
		}
	}
	
	private <F, V> void infoMasquee (Tapis<Carte <F, V>> tapisReel, List<Integer> cartesChoisies) {
		for (final int iCarte : cartesChoisies) {
			try {
				tapisReel.masquer(iCarte);
			} catch (PositionInvalideException e) {
				System.out.println("Dammed! Encore rate!");
			}
		}
	}
	
	private <F, V> void requeteCarte (Joueur joueur, Tapis<Carte <F, V>> tapis, Tapis<Carte <F, V>> tapisReel, List<Integer> cartesChoisies, int iCarte) {
		Integer iCarteChoisie;
		do {
			iCarteChoisie = demandeEntree(joueur, tapis, tapisReel, iCarte);
		} while (cartesChoisies.contains(iCarteChoisie));

		
		try {
			tapisReel.montrer(iCarteChoisie);
			Carte<F, V> curCarte = tapisReel.get(iCarteChoisie);
			System.out.println(joueur.getNom() + " retourne la carte #"+ (iCarte+1) +" à la position " + iCarteChoisie + " : " + curCarte.getFamille() + " " + curCarte.getValeur());
			cartesChoisies.add(iCarteChoisie);
		} catch (PositionInvalideException e) {
			System.out.println("La carte ne possede pas la bonne position");
		}
		
		System.out.println(afficheur.toString(tapisReel));
		
		infoRetournee(joueur, tapis, tapisReel, iCarte, iCarteChoisie); //bug ici pour l'humain
	}
	
	private <F, V> boolean tourJoueur(Joueur joueur, Tapis<Carte <F, V>> tapis, Tapis<Carte <F, V>> tapisReel, int tailleFamille) throws OperationInvalideException {
		System.out.println("C’est au tour de " + joueur.getNom() + ".");
		
		afficheur.toString(tapis);
		List<Integer> cartesChoisies = new ArrayList<Integer>();
		for (int iCarte = 0; iCarte < tailleFamille; iCarte++) {
			requeteCarte(joueur, tapis, tapisReel, cartesChoisies, iCarte);
		}
		
		if (isFamille(tapisReel, cartesChoisies)) {
			infoPrise(joueur, tapis, tapisReel, cartesChoisies);
			return true;
		}
		
		System.out.println(joueur.getNom() + " n'a trouvé de famille.");
		infoMasquee(tapisReel, cartesChoisies);
		
		return false;
	}
	
	private <F, V> boolean jouerTour(Tapis<Carte<F, V>> tapis, Tapis<Carte<F, V>> tapisReel, int tailleFamille, int iJoueur) {
		Joueur curJoueur = joueurs.get(iJoueur);
		try {
			if (tourJoueur(curJoueur, tapis, tapisReel, tailleFamille)) {
				scores.ajouter(curJoueur, tailleFamille); // On ajoute le score au joueur
				System.out.println(curJoueur.getNom() + " a trouvé une famille, marque " + tailleFamille + " points et rejoue.");
				return true;
			}
		} catch (OperationInvalideException e) {
			System.out.println("Elimination du joueur : " + curJoueur.getNom() + " pour triche");
			joueurs.remove(iJoueur);
		} catch (AbandonException e) {
			System.out.println(curJoueur.getNom() + " abandonne !");
			joueurs.remove(iJoueur);
		}
		return false;
	}
	
	private <F, V> void jouer(Tapis<Carte<F, V>> tapis, Tapis<Carte<F, V>> tapisReel, int tailleFamille) {
		for (int iJoueur = 0; tapis.nbCartesRestantes() > 0; iJoueur = (iJoueur+1)%joueurs.size()) {
			if (jouerTour(tapis, tapisReel, tailleFamille, iJoueur)) {
				iJoueur--;
			}
			System.out.println("");
			if (joueurs.size() == 0) {
				break;
			}
		}
	}
	
	/** Arbitrer une partie de Memory.  La taille de famille utilisée doit être
	 * un diviseur de la taille d'une famille du jeu de carte.
	 * @param jeu le jeu de carte à utliser
	 * @param tailleFamille la taille d'une famille à utilise.
	 * @param <F> le type des familles du jeu de cartes
	 * @param <V> le type des valeurs du jeu de cartes
	 */
	public <F, V> void arbitrer(JeuCartesMemory<F, V> jeu, int tailleFamille) {
		arbitrer(jeu, tailleFamille, true);
	}
	
	/** Arbitrer une partie de Memory.  La taille de famille utilisée doit être
	 * un diviseur de la taille d'une famille du jeu de carte.
	 * @param jeu le jeu de carte à utliser
	 * @param tailleFamille la taille d'une famille à utilise.
	 * @param mode mefiant si vrai
	 * @param <F> le type des familles du jeu de cartes
	 * @param <V> le type des valeurs du jeu de cartes
	 */
	public <F, V> void arbitrer(JeuCartesMemory<F, V> jeu, int tailleFamille, boolean mode) {
		Tapis<Carte<F, V>> tapisReel = new TapisReel<Carte<F, V>>(jeu);
		Tapis<Carte<F, V>> tapis = tapisReel;
		
		if (mode) {
			tapis = new TapisProcuration<Carte<F, V>>(tapisReel);
		}

		System.out.println(afficheur.toString(tapisReel));
		
		for (final Joueur joueur : joueurs) {
			joueur.commencer(tailleFamille);
		}
		
		jouer(tapis, tapisReel, tailleFamille);
		
		System.out.println("La partie est finie. Voici les scores :");
		System.out.println(scores);
	}

}
