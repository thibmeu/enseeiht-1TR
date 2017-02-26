import java.awt.Color;
import java.util.Arrays;

/** Polygone modélise un polygone géométrique dans un plan équipé d'un
 * repère cartésien.  Un polygone peut être affiché et translaté.
 * Sa couleur peut etre obtenue. Des points peuvent etre ajoute.
 *
 * @author  Thibault Meunier
 * @version 1
 */

public class Polygone {
    /** Attribut sommet.
     * @param sommets sommets du Polygone
     */
	private Point[] sommets;
    /** Attribut couleur.
     * @param couleur couleur du Polygone
     */
    private Color couleur;

	/** Construire un Polygone à partir de ses sommets.
	 * @param nSommets sommets du polygone
	 */
	public Polygone(Point... nSommets) {
		this(Color.blue, nSommets);
	}

    /** Test si le tableau contient des points null.
     * @param point tableau de points
     * @return true si aucun point null dans le tableau
     */
    private boolean noNullArray(Point[] point) {
        for (final Point curPoint : point) {
            if (curPoint == null) {
                return false;
            }
        }
        return true;
    }

	/** Construire un Polygone à partir de sa couleur et de ses sommets.
	 * @param nCouleur couleur
	 * @param nSommets sommetss du polygone
	 */
	public Polygone(Color nCouleur, Point... nSommets) {
		assert nCouleur != null && noNullArray(nSommets);
        couleur = nCouleur;
		sommets = new Point[nSommets.length];
        for (int iSommet = 0; iSommet < sommets.length; iSommet++) {
            //La methode qui suit devrait etre dans Point !!!
        	Point curSommet = nSommets[iSommet];
        	sommets[iSommet] = new Point(curSommet.getX(), curSommet.getY());
        	sommets[iSommet].setCouleur(curSommet.getCouleur());
        }
	}

    /** Retourne la chaine de caracteres representant le Polygone.
     * @return cf commentaire ci-dessus
     */
	public String toString() {
		String coor = "";
		for (final Point cursommets : sommets) {
			coor += cursommets + " ";
		}
		return "<< " + coor + ">>";
	}

	/** Obtenir la couleur du polygone.
	 * @return la couleur du polygone
	 */
	public Color getCouleur() {
		return couleur;
	}

	/** Changer la couleur du polygone.
	 * @param nCouleur nouvelle couleur
	 */
	public void setCouleur(Color nCouleur) {
		assert nCouleur != null;
		couleur = nCouleur;
	}

	/** Teste si un indice de sommets est dans le polygone.
	 * @param iSommet indice a tester
	 * @return True si 0 <= iSommet < nbsommetss
	 */
	private boolean isValidsommets(int iSommet) {
        return 0 <= iSommet && iSommet < getOrdre();
	}

	/** Obtenir le iSommet-eme sommets du polygone.
	 * @param iSommet indice du sommets
	 * @return sommets (point) asocie a l'indice
	 */
	public Point getSommet(int iSommet) {
        assert isValidsommets(iSommet);
		Point curPoint = sommets[iSommet];
        //Encore une methode a implementer dans Point
		Point rPoint = new Point(curPoint.getX(), curPoint.getY());
        rPoint.setCouleur(curPoint.getCouleur());
		return rPoint;
	}

	/** Obtenir l'ordre du polygone.
	 * @return ordre du polygone
	 */
	public int getOrdre() {
		return sommets.length;
	}

	/** Ajouter un sommets a la fin du polygone.
	 * @param nPoint sommets a ajouter
	 */
	public void ajouter(Point nPoint) {
        ajouter(nPoint, getOrdre());
	}

	/** Ajouter un sommets a la fin du polygone.
	 * @param nCouleur couleur
	 * @param nPoint sommets a ajouter
	 */
	private void ajouter(Color nCouleur, Point nPoint) {
        ajouter(nCouleur, nPoint, getOrdre());
	}

	/** Ajouter un sommets au polygone.
	 * @param nPoint sommets a ajouter
	 * @param iNPoint indice d'insertion
	 */
	public void ajouter(Point nPoint, int iNPoint) {
		assert nPoint != null;
        ajouter(nPoint.getCouleur(), nPoint, iNPoint);
	}

	/** Ajouter un sommets au polygone.
	 * @param nCouleur couleur
	 * @param nPoint sommets a ajouter
	 * @param iNPoint indice d'insertion
	 */
	private void ajouter(Color nCouleur, Point nPoint, int iNPoint) {
		assert nCouleur != null && nPoint != null;
        assert isValidsommets(iNPoint) || (iNPoint == getOrdre());
		Point curPoint = new Point(nPoint.getX(), nPoint.getY());
		curPoint.setCouleur(nCouleur);
		insert(iNPoint, curPoint);
	}

    /** Insere un point a un emplacement.
     * @param iNPoint indice du point a inserer
     * @param curPoint point a inserer
     */
    private void insert(int iNPoint, Point curPoint) {
        sommets = Arrays.copyOf(sommets, sommets.length + 1);
        for (int iSommet = sommets.length - 1; iSommet > iNPoint; iSommet--) {
            sommets[iSommet] = sommets[iSommet - 1];
        }
        sommets[iNPoint] = curPoint;
    }

	/** Translater le polygone.
	 * @param dx déplacement suivant l'axe des X
	 * @param dy déplacement suivant l'axe des Y
	 */
	public void translater(double dx, double dy) {
        for (final Point curPoint : sommets) {
			curPoint.translater(dx, dy);
		}
	}

	/** Determiner le perimetre du polygone.
	 * @return distance entre this et autre
	 */
	public double perimetre() {
		double peri = 0;
		for (int iSommet = 0; iSommet < sommets.length; iSommet++) {
            Point nextSommet = sommets[(iSommet + 1) % sommets.length];
			peri += sommets[iSommet].distance(nextSommet);
		}
		return peri;
	}

	/** Construire un rectangle à partir de ses deux sommets opposes.
	 * @param a sommet du rectangle
	 * @param c sommet oppose a a
     * @return rectangle dont a et c sont deux sommets
	 */
	public static Polygone creerRectangle(Point a, Point c) {
		assert a != null && c != null;
		assert a.getX() != c.getX() && a.getY() != c.getY();

        if (a.getX() > c.getX()) {
        	Point tmpA = a;
        	a = c;
        	c = tmpA;
        }

        Point b = new Point(c.getX(), a.getY());
    	Point d = new Point(a.getX(), c.getY());

        if (a.getY() > c.getY()) {
        	Point tmpB = b, tmpD = d;
        	b = c;
        	d = a;
        	a = tmpD;
        	c = tmpB;
        }
		return new Polygone(a, b, c, d);
	}
}
