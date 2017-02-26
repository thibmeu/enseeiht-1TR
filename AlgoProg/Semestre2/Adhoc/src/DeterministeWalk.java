/**
 * @author Thibault Meunier
 * @version 1.0
 */

public class DeterministeWalk extends AbstractMobilite {
	
    private double vitesse;
    private double angle;

    public DeterministeWalk(double v, double a, double dt) {
        super(dt);
        vitesse = v;
        angle = a;
    }

	/** Fonction qui permet de rapprocher le noeud de sa cible
	 * @param position
	 * @param temps temps de déplacement
	 */
	public Position progressionTemps(Position position, double temps) {
        return progressionDistance(position, vitesse*temps);
    }
	
	/** Fonction qui permet de rapprocher le noeud de sa cible
	 * @param position
	 * @param distance deplacement
	 */
	public Position progressionDistance(Position position, double distance) {
        if (isChemin()) {
            return removeChemin();
        }
        return new Position(position.getX() + distance*cos(a), position.getY()+distance*sin(a));
    }

}
