import java.awt.Color;

/** Modélisation d'un cercle.
 * @author  Xavier Crégut
 * @version 1.10
 */

public class Cercle
{
	//@ public invariant getRayon() >= 0;

	/** Le centre du cercle */
	private Point centre;

	/* couleur du cercle */
	private Color couleur;

	/** Le rayon du cercle */
	private double rayon;

	public final static double EPSILON = 1.0e-5;

	/**  Construire un cercle à partir de son centre et son rayon.
	 * @param centre point centre du cercle
	 * @param rayon rayon du cercle (positif)
	 */
	//@ requires rayon >= 0;			// rayon positif
	//@
	//@ ensures getRayon() == rayon;		// rayon initialisé
	//@ ensures getCentre().equals(centre);	// centre initialisé
	public Cercle(Point sonCentre, double sonRayon) {
		this.centre = sonCentre;
		this.rayon = sonRayon;
		this.couleur = Color.green;
	}

	/** Construire un cercle à partir de deux points diamétralement opposés.
	 * @param p1 le premier point
	 * @param p2 le deuxième point
	 */
	//@ensures getRayon() == p1.distance(p2) / 2;
	public Cercle(Point p1, Point p2) {
		double cx = (p1.getX() + p2.getX()) / 2;
		double cy = (p1.getY() + p2.getY()) / 2;
		this.centre = new Point(cx, cy);
		this.rayon = p1.distance(p2) / 2;
		this.couleur = Color.green;
	}

	/** Obtenir le centre du cercle.
	 * @return le centre du cercle
	 */
	public Point getCentre() {
		return this.centre;
	}

	/** Obtenir le rayon du cercle.
	 * @return le rayon du cercle
	 */
	public double getRayon() {
		return this.rayon;
	}

	/** Afficher le cercle.  Le cercle est affiché sous la forme :
	 * <PRE>
	 *		Cercle[centre;rayon]
	 * </PRE>
	 */
	public void afficher() {
		System.out.print("Cercle[");
		this.getCentre().afficher();
		System.out.print(";");
		System.out.print(this.getRayon());
		System.out.print("]");
	}

   /** Translater le cercle.
	* @param dx déplacement suivant l'axe des X
	* @param dy déplacement suivant l'axe des Y
	*/ 
	public void translater(double dx, double dy) {
		this.centre.translater(dx, dy);
	}

	/** Dessiner le cercle sur l'afficheur
	 * @param afficheur l'afficheur à utiliser
	 */
	public void dessiner(afficheur.Afficheur afficheur) {
		afficheur.dessinerCercle (this.getCentre().getX(),
					this.getCentre().getY(),
					this.getRayon(), this.getCouleur());

		// On dessine également le centre.  Est-ce logique ?
		this.getCentre().dessiner(afficheur);
	}

	/** Changer le rayon du cercle.
	 * @param nouveauRayon nouveau rayon du cercle
	 */
	//@requires nouveauRayon >= 0;	// le rayon est positif
	//@ensures getRayon() == nouveauRayon;	// le rayon est changé
	public void setRayon(double nouveauRayon) {
		this.rayon = nouveauRayon;
	}

	/** Changer le diamètre du cercle.
	 * @param nouveauDiametre nouveau diamètre du cercle
	 */
	//@ requires nouveauDiametre >= 0;	// le diamètre est positif
	//@ ensures Math.abs(getRayon() * 2 - nouveauDiametre) < EPSILON;
	//@			//  le diamètre est changé
	public void setDiametre(double nouveauDiametre) {
		this.rayon = nouveauDiametre / 2;
	}

	/** Obtenir le périmètre du cercle.
	 * @return le périmètre du cercle
	 */
	//@ ensures Math.abs(\result - 2 * Math.PI * getRayon()) < EPSILON;
	public double getPerimetre() {
		return 2 * Math.PI * this.rayon;
	}

	/**  Obtenir la surface du cercle.
	 * @return la surface du cercle
	 */
	//@ ensures Math.abs(\result - Math.PI * getRayon() * getRayon()) < EPSILON;
	public double getSurface() {
		return Math.PI * this.rayon * this.rayon;
	}

	/** Obtenir la couleur du cercle.
	 * @return la couleur du cercle
	 */
	public Color getCouleur() {
		return this.couleur;
	}

	/** Changer la couleur du cercle.
	  * @param nouvelleCouleur nouvelle couleur
	  */
	public void setCouleur(Color nouvelleCouleur) {
		this.couleur = nouvelleCouleur;
	}

}
