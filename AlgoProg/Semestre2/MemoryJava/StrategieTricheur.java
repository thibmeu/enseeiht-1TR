import java.util.*;

public class StrategieTricheur extends AbstractStrategie {
	
	private boolean premiere = true;
	
	/** Méthode appelée par l'arbitre pour demander la carte choisie
	 * par le joueur.
	 * @param numero le numéro de la carte demandée (1 pour la première)
	 * @param tapis le tapis de jeu du Memory
	 * @throws OperationInvalideException 
	 * @throws CarteVisibleException 
	 */
	public int carteChoisie(int numero, Tapis<? extends Carte<?, ?>> tapis) throws OperationInvalideException {
		if (premiere) {
			memoire = new Memoire(tapis);
		}
		
		//on prend la premiere famille et on la fait !
		return choixExpert(tapis);
	}
	
}
