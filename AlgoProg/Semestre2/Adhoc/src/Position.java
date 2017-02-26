/**
 * Cette classe est utilisé pour gérer plus facilement
 * la position des noeuds
 * @author LAMINE Abdelmalek
 * @version 1.0
 */

public class Position {
	
	/** Abscisse */
	private double x;
	
	/** Ordonné*/
	private double y;
	
	public Position(double abs, double ord) {
		x = abs;
		y = ord;
	}
	
	public void setX(double nvX) {
		x = nvX;
	}
	
	public void setY(double nvY) {
		y = nvY;
	}
	
	
	/**@return l'abscisse du noeuds*/
	public double getX() {
		return x;
	}
	
	/**@return l'ordonné du point*/
	public double getY() {
		return y;
	}
	
	/**
	 * permet de translater le noeud
	 */
	public void transler(double dx, double dy) {
		double nvX = x + dx;
		double nvY = y + dy;
		this.setX(nvX);
		this.setY(nvY);
	}
	
	
	public static double distance(Position pos1, Position pos2) {
		 	return Math.sqrt(Math.pow(pos1.getX() - pos2.getX(), 2)
				+ Math.pow(pos1.getX() - pos2.getY(), 2));

	}
	
}
