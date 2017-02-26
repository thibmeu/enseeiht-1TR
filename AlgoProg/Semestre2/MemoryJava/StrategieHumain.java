import java.util.Scanner;

public class StrategieHumain extends AbstractStrategie {
	
	private Scanner input = new Scanner(System.in);
	
	/** Méthode appelée par l'arbitre pour demander la carte choisie
	 * par le joueur.
	 * @param numero le numéro de la carte demandée (1 pour la première)
	 * @param tapis le tapis de jeu du Memory
	 * @throws AbandonException 
	 */
	public int carteChoisie(int numero, Tapis<? extends Carte<?, ?>> tapis) throws AbandonException {
		int iCarteChoisie = 0;

		boolean carteOk = false;
		do {
			System.out.print("Position de la carte #" + (numero+1) + " à retourner : ");
			String requete = input.next();
			try {
				iCarteChoisie = Integer.parseInt(requete);
			} catch (NumberFormatException e) {
				if (requete.equals("ABANDON")) {
					throw new AbandonException("J'me tire -- Maitre Gims");
				}
				throw e;
			}
			
			try {
				carteOk = tapis.estPrise(iCarteChoisie) || tapis.estVisible(iCarteChoisie);
			} catch (PositionInvalideException e) {
				System.out.println("La carte choisie n'est pas a la bonne position " + iCarteChoisie + e.getMessage());
			} catch (CartePriseException e) {
				;
			}
			
		} while (iCarteChoisie < 0 || iCarteChoisie >= tapis.taille() || carteOk);
		
		return iCarteChoisie;
	}
	
	public void carteRetournee(String nomJoueur, int numero, int position, Tapis<? extends Carte<?, ?>> tapis) {
		Scanner tmp = new Scanner(System.in);
		System.out.println("Appuyez sur Entree");
		tmp.nextLine();
	}
	
}
