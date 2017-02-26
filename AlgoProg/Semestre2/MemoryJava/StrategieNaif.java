import java.util.*;

public class StrategieNaif extends AbstractStrategie {

	/** Méthode appelée par l'arbitre pour demander la carte choisie
	 * par le joueur.
	 * @param numero le numéro de la carte demandée (1 pour la première)
	 * @param tapis le tapis de jeu du Memory
	 */
	public int carteChoisie(int numero, Tapis<? extends Carte<?, ?>> tapis) {
		int iCarteChoisie = 0;
		boolean ok = false;
		do {
			iCarteChoisie = new Random().nextInt(tapis.nbCartesRestantes());
			try {
				ok = tapis.estPrise(iCarteChoisie) || tapis.estVisible(iCarteChoisie);
			} catch (PositionInvalideException e) {
				System.out.println("La carte choisie n'est pas a la bonne position " + iCarteChoisie + e.getMessage());
			} catch (CartePriseException e) {
				;
			}
		} while (ok);
		return iCarteChoisie;
	}

	/** Événement qui indique qu'une carte a été retournée et est donc visible.
	 * @param nomJoueur le nom du joueur qui l'a prise
	 * @param numero le numéro de la carte retournée (1 pour la première)
	 * @param position la position de la carte prise sur le tapis
	 * @param tapis le tapis sur lequel la carte a été prise
	 */
	public void carteRetournee(String nomJoueur, int numero, int position, Tapis<? extends Carte<?, ?>> tapis) {
		;
	}

	/** Événement qui indique qu'une carte a été prise.
	 * @param nomJoueur le nom du joueur qui l'a prise
	 * @param position la position de la carte prise sur le tapis
	 * @param tapis le tapis sur lequel la carte a été prise
	 */
	public void cartePrise(String nomJoueur, int position, Tapis<? extends Carte<?, ?>> tapis) {
		;
	}
	
}
