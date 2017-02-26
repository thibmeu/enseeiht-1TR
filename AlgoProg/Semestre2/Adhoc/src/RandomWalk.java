/**
 * @author Driouich Ilias
 * @author Thibault Meunier
 * @version 1.3
 */

public class RandomWalk extends AbstractMobilite {
	
	/** Fonction qui permet de rapprocher le noeud de sa cible
	 * @param position
	 * @param temps temps de déplacement
	 */
	public Position progressionTemps(Position position, double temps);
	
	/** Fonction qui permet de rapprocher le noeud de sa cible
	 * @param position
	 * @param distance deplacement
	 */
	public Position progressionDistance(Position position, double temps);

}
