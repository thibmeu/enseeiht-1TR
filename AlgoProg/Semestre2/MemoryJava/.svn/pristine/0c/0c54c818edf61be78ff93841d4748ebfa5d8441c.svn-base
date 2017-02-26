
public class TapisProcuration<C> implements Tapis<C> {
	
	private Tapis<C> cartes;
	
	public TapisProcuration (Tapis<C> cartes) {
		this.cartes = cartes;
	}
	
	/** La taille du tapis.
	  * @return la taille du tapis
	  */
	public int taille() {
		return cartes.taille();
	}

	/** Le nombre de cartes encore présentes sur le tapis.
	  * @return le nombre de cartes encore présentes sur le tapis
	  */
	public int nbCartesRestantes() {
		return cartes.nbCartesRestantes();
	}

	/** Rendre visible une carte de ce tapis.
	  * @param position position de la carte
	  * @throws OperationInvalideException le joueur triche
	  */
	public void montrer(int position) throws OperationInvalideException {
		throw new OperationInvalideException("Tricheur");
	}

	/** Retourner la carte pour qu'elle soit face cachée.
	  * @param position position de la carte
	  * @throws OperationInvalideException le joueur triche
	  */
	public void masquer(int position) throws OperationInvalideException {
		throw new OperationInvalideException("Tricheur");
	}

	/** Prendre une carte de ce tapis.
	  * @param position position de la carte
	  * @throws OperationInvalideException le joueur triche
	  */
	public void prendre(int position) throws OperationInvalideException {
		throw new OperationInvalideException("Tricheur");
	}

	/** Savoir si une carte a été prise.
	  * @param position position de la carte
	  * @return vrai si la carte a été prise
	  * @throws PositionInvalideException la position est invalide
	  */
	public boolean estPrise(int position) throws PositionInvalideException {
		return cartes.estPrise(position);
	}

	/** Savoir si une carte est visible.
	  * @param position position de la carte
	  * @return vrai si la carte est visible
	  * @throws PositionInvalideException la position est invalide
	  * @throws CartePriseException la carte a été prise
	  */
	public boolean estVisible(int position) throws PositionInvalideException {
		return cartes.estVisible(position);
	}

	/** Obtenir une carte de ce tapis.
	  * @param position position de la carte
	  * @return la carte à la position indiquée
	  * @throws PositionInvalideException la position est invalide
	  * @throws CarteMasqueeException la carte a été prise
	  * @throws CartePriseException la carte a été prise
	  */
	public C get(int position) throws PositionInvalideException {
		return cartes.get(position);
	}
}
