import java.util.ArrayList;
import java.util.List;

public class TapisReel<C extends Carte<?,?>> implements Tapis<C> {
	
	private List<CarteEtat<C>> cartes = new ArrayList<CarteEtat<C>>();
	
	public TapisReel (JeuCartes<C> cartes) {
		for (C curCarte : cartes) {
			this.cartes.add(new CarteEtat<C>(curCarte));
		}
	}
	
	/** La taille du tapis.
	  * @return la taille du tapis
	  */
	public int taille() {
		return cartes.size();
	}

	/** Le nombre de cartes encore présentes sur le tapis.
	  * @return le nombre de cartes encore présentes sur le tapis
	  */
	public int nbCartesRestantes() {
		int nbCartes = 0;
		for (CarteEtat<C> curCarte : cartes) {
			if (curCarte.getEtat() != CarteEtat.Etat.RETIREE) {
				nbCartes++;
			}
		}
		return nbCartes;
	}
	
	private void isValidePosition(int position) throws PositionInvalideException {
		if (position >= cartes.size() || position < 0) {
			throw new PositionInvalideException("Position invalide : " + position);
		}
	}
	
	/** Rendre visible une carte de ce tapis.
	  * @param position position de la carte
	  * @throws PositionInvalideException la position est invalide
	  * @throws CartePriseException la carte a été prise
	  * @throws CarteVisibleException la carte est visible
	 * @throws OperationInvalideException 
	  */
	public void montrer(int position) throws PositionInvalideException, CartePriseException, CarteVisibleException, OperationInvalideException {
		isValidePosition(position);
		
		switch (cartes.get(position).getEtat()) {
		case VISIBLE:
			throw new CarteVisibleException("Une carte VISIBLE ne peut etre montree");
		case RETIREE:
			throw new CartePriseException("Une carte RETIREE ne peut etre montree");
		case CACHEE:
			cartes.get(position).setEtat(CarteEtat.Etat.VISIBLE);
			break;
		}
	}

	/** Retourner la carte pour qu'elle soit face cachée.
	  * @param position position de la carte
	  * @throws PositionInvalideException la position est invalide
	  * @throws CartePriseException la carte a été prise
	  * @throws CarteMasqueeException la carte est face cachée
	  */
	public void masquer(int position) throws PositionInvalideException, CartePriseException, CarteMasqueeException, OperationInvalideException {
		isValidePosition(position);
		
		switch (cartes.get(position).getEtat()) {
		case CACHEE:
			throw new CarteMasqueeException("Une carte CACHEE ne peut etre masquee");
		case RETIREE:
			throw new CartePriseException("Une carte RETIREE ne peut etre masquee");
		case VISIBLE:
			cartes.get(position).setEtat(CarteEtat.Etat.CACHEE);
		}
	}

	/** Prendre une carte de ce tapis.
	  * @param position position de la carte
	  * @throws PositionInvalideException la position est invalide
	  * @throws CartePriseException la carte a été prise
	 * @throws OperationInvalideException 
	  */
	public void prendre(int position) throws PositionInvalideException, CartePriseException, OperationInvalideException {
		isValidePosition(position);
		
		CarteEtat<C> curCarte = cartes.get(position);
		if (curCarte.getEtat() == CarteEtat.Etat.RETIREE)
			throw new CartePriseException("Une carte RETIREE ne peut etre prise");
		curCarte.setEtat(CarteEtat.Etat.RETIREE);
	}
	
	public boolean estEtat(int position, CarteEtat.Etat etat) throws PositionInvalideException {
		isValidePosition(position);
		
		return cartes.get(position).getEtat() == etat;
	}
	
	/** Savoir si une carte a été prise.
	  * @param position position de la carte
	  * @return vrai si la carte a été prise
	  * @throws PositionInvalideException la position est invalide
	  */
	public boolean estPrise(int position) throws PositionInvalideException {
		isValidePosition(position);
		return estEtat(position, CarteEtat.Etat.RETIREE);
	}

	/** Savoir si une carte est visible.
	  * @param position position de la carte
	  * @return vrai si la carte est visible
	  * @throws PositionInvalideException la position est invalide
	  * @throws CartePriseException la carte a été prise
	  */
	public boolean estVisible(int position) throws PositionInvalideException {
		if (cartes.get(position).getEtat() == CarteEtat.Etat.RETIREE)
			throw new CartePriseException("La carte a deja ete retiree du jeu");
		
		return estEtat(position, CarteEtat.Etat.VISIBLE);
	}

	/** Obtenir une carte de ce tapis.
	  * @param position position de la carte
	  * @return la carte à la position indiquée
	  * @throws PositionInvalideException la position est invalide
	  * @throws CarteMasqueeException la carte a été prise
	  * @throws CartePriseException la carte a été prise
	  */
	public C get(int position) throws PositionInvalideException {
		isValidePosition(position);
		switch (cartes.get(position).getEtat()) {
		case CACHEE:
			throw new CarteMasqueeException("Une carte CACHEE ne peut etre obtenue");
		case RETIREE:
			throw new CartePriseException("Une carte RETIREE ne peut etre obtenue");
		case VISIBLE:
			return (C)cartes.get(position).getCarte();
		}
		return null;
		
	}
}
