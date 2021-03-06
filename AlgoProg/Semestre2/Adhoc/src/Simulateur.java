import java.util.PriorityQueue;

/**
 * 
 * Classe modelisant un simulateur à événements discrets
 * @author Driouich Ilias
 * @version 1.0
 */

public class Simulateur {
	
	private PriorityQueue<Evenement> evenements = new PriorityQueue<Evenement>();
	private int dateCourante = 0;
	
	/** Fonction qui execute un evenement 
	 * @param evenement l'événement à éxecuter 
	 */
	public void enregistrer(Evenement evenement ) {
		evenements.add(evenement);
	
	}
	public int getDateCourante(){
		return dateCourante;
	}
	public void avancer(int dt) {
		dateCourante += dt;
		
	}
}
