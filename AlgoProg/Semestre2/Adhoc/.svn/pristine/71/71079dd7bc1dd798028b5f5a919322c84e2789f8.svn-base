/**
 * @author Driouich Ilias
 * @version 1.0
 */

import java.util.List;
import java.util.ArrayList;

public abstract class AbstractMobilite implements Mobilite {
	private List<Position> chemin = new ArrayList<Position>();
    private double dt;

    public AbstractMobilite(double dt) {
        this.dt = dt;
    }

    public double getPas() {
        return dt;
    }

    protected boolean isChemin() {
        return !chemin.empty();
    }

    protected void addChemin(Position pos) {
        chemin.add(pos);
    }

    protected Position removeChemin() {
        return chemin.remove(0);
    }

    /** Fonction qui permet de rapprocher le noeud de sa cible
	 * @param position
	 * @param temps temps de déplacement
	 */
	public abstract Position progressionTemps(Position position, double temps);
	
    public Position progressionTemps(Position source, double temps, Positiondestination) {
        double distance = Position.distance(source, destination);
        double dx = distance*dt/temps;
        while (temps > dt) {
            addChemin(new Position(destination.getX() + dx, destination.dx()));
        //il manque le dernier point ici
    }

    /** Fonction qui permet de rapprocher le noeud de sa cible
	 * @param position
	 * @param distance distance de déplacement
	 */
	public abstract Position progressionDistance(Position position, double distance);

	public Position progression(Position position, double distance, double temps) {
        
    }
}
	
