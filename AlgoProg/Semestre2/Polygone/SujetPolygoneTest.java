import java.awt.Color;
import org.junit.*;
import static org.junit.Assert.*;

/**
  * Tests permettant de vérifier les exigences et contraintes exprimées dans le
  * sujet.
  *
  * @author	Xavier Crégut
  * @version	$Revision: 1.2 $
  */
public class SujetPolygoneTest {

	// précision pour les comparaisons entre nombres réels
	public final static double EPSILON = 0.001;

	// Les points du sujet
	private Point A, B, C, D, E, F;
	private Point R, S, T;
	private Point I, J, K, L;

	// Les polygones du sujet
	private Polygone ABCDEF;
	private Polygone RST;
	private Polygone IJKL;

	@Before public void setUp() {
		// Construire les points
		A = new Point(9, 1);
		B = new Point(7, 4);
		C = new Point(11, 5);
		D = new Point(12, 3);
		E = new Point(10, 3);

		R = new Point(2, -1);
		S = new Point(5, -1);
		T = new Point(4, 3);

		I = new Point(-3, 4);
		J = new Point(1, 1);
		K = new Point(1, 4);
		L = new Point(-3, 1);

		// Construire les polygones
		ABCDEF = new Polygone(A, B, C, D, E);
		RST = new Polygone(R, S, T);
		IJKL = new Polygone(I, J, K, L);
	}

	@Test public void testerTranslater() {
		RST.translater(5, 7);
		memesCoordonnees("E1 non respectée", new Point(7,  6), RST.getSommet(0));
		memesCoordonnees("E1 non respectée", new Point(10, 6), RST.getSommet(1));
		memesCoordonnees("E1 non respectée", new Point(9, 10), RST.getSommet(2));
	}

	@Test public void testerOrdre() {
		assertEquals("E2 : Ordre incorrect.", 3, RST.getOrdre());
		assertEquals("E2 : Ordre incorrect.", 4, IJKL.getOrdre());
		assertEquals("E2 : Ordre incorrect.", 5, ABCDEF.getOrdre());
	}

	@Test public void testerInitialisationRST() {
		verifierSommetsRST("E3");
	}

	private void verifierSommetsRST(String exigence) {
		String message = exigence + " : Erreur sur le sommet ";
		memesCoordonnees(message + "0.", R, RST.getSommet(0));
		memesCoordonnees(message + "1.", S, RST.getSommet(1));
		memesCoordonnees(message + "2.", T, RST.getSommet(2));
	}

	@Test public void testerCouleur() {
		assertEquals("E8: Couleur initiale par défaut incorrecte.",
				Color.blue, RST.getCouleur());

		// Changer de la couleur
		RST.setCouleur(Color.red);
		assertEquals("E5: Erreur sur changement de la couleur.",
				Color.red, RST.getCouleur());

		// Utiliser la couleur dans le constructeur
		RST = new Polygone(Color.yellow, R, S, T);
		assertEquals("E5: Erreur sur changement de la couleur.",
				Color.yellow, RST.getCouleur());
		verifierSommetsRST("E7");	// Le polygone est correctement créé.
	}

	@Test public void testerCouleurPoints() {
		R.setCouleur(Color.RED);
		S.setCouleur(Color.YELLOW);
		T.setCouleur(Color.CYAN);
		RST = new Polygone(Color.GREEN, R, S, T);
		String message = "La couleur du point a changé !";
		assertEquals(message, Color.RED, RST.getSommet(0).getCouleur());
		assertEquals(message, Color.YELLOW, RST.getSommet(1).getCouleur());
		assertEquals(message, Color.CYAN, RST.getSommet(2).getCouleur());
		A.setCouleur(Color.ORANGE);
		RST.ajouter(A, 0);
		assertEquals(message, Color.ORANGE, RST.getSommet(0).getCouleur());
	}


	@Test public void testerToString() {
		assertEquals("E6: toString() redéfinie ? Correctement ?",
				"<< (2.0, -1.0) (5.0, -1.0) (4.0, 3.0) >>", RST.toString());
		assertEquals("E6: toString() redéfinie ? Correctement ?",
				"<< (-3.0, 4.0) (1.0, 1.0) (1.0, 4.0) (-3.0, 1.0) >>", IJKL.toString());
	}

	@Test public void testerAjouterDebut() {
		RST.ajouter(J, 0);
		String message = "E11 : Erreur sur ajouter";
		memesCoordonnees(message, J, RST.getSommet(0));
		memesCoordonnees(message, R, RST.getSommet(1));
		memesCoordonnees(message, S, RST.getSommet(2));
		memesCoordonnees(message, T, RST.getSommet(3));
	}

	@Test public void testerAjouterFin() {
		RST.ajouter(J, 3);
		String message = "E11 : Erreur sur ajouter";
		memesCoordonnees(message, R, RST.getSommet(0));
		memesCoordonnees(message, S, RST.getSommet(1));
		memesCoordonnees(message, T, RST.getSommet(2));
		memesCoordonnees(message, J, RST.getSommet(3));
	}

	@Test public void testerAjouterFinBis() {
		RST.ajouter(J);
		String message = "E11 : Erreur sur ajouter";
		memesCoordonnees(message, R, RST.getSommet(0));
		memesCoordonnees(message, S, RST.getSommet(1));
		memesCoordonnees(message, T, RST.getSommet(2));
		memesCoordonnees(message, J, RST.getSommet(3));
	}

	@Test public void testerAjouter1() {
		RST.ajouter(J, 1);
		String message = "E11 : Erreur sur ajouter";
		memesCoordonnees(message, R, RST.getSommet(0));
		memesCoordonnees(message, J, RST.getSommet(1));
		memesCoordonnees(message, S, RST.getSommet(2));
		memesCoordonnees(message, T, RST.getSommet(3));
	}

	@Test public void testerAjouter2() {
		RST.ajouter(J, 2);
		String message = "E11 : Erreur sur ajouter";
		memesCoordonnees(message, R, RST.getSommet(0));
		memesCoordonnees(message, S, RST.getSommet(1));
		memesCoordonnees(message, J, RST.getSommet(2));
		memesCoordonnees(message, T, RST.getSommet(3));
	}

	@Test public void testerAjouterAutresMethodes() {
		RST.ajouter(new Point(5, 3), 2);
		RST.ajouter(new Point(2, 3), 4);
		assertEquals(5, RST.getOrdre());
	}


	@Test public void testerEncapsulationGetSommet() {
		RST.getSommet(0).translater(.5, 3.5);
		memesCoordonnees("E9 : Translater un sommet ne devrait pas modifier "
				+ "le polygone", new Point(2, -1), RST.getSommet(0));
	}

	@Test public void testerEncapsulationConstructeur() {
		R.translater(.5, 3.5);
		memesCoordonnees("E9 : Translater un point passé en paramètre du "
				+ "constructeur ne devrait pas modifier le polygone",
				new Point(2, -1), RST.getSommet(0));
	}

	@Test public void testerEncapsulationConstructeurCouleur() {
		RST = new Polygone(Color.RED, R, S, T);
		testerEncapsulationConstructeur();
	}

	@Test public void testerEncapsulationAjouterSommetFin() {
		RST.ajouter(J);
		J.translater(.5, 3.5);
		memesCoordonnees("E9 : Translater un point ajouté comme sommet "
				+ "ne devrait pas modifier le polygone",
				new Point(1, 1), RST.getSommet(3));
	}

	@Test public void testerEncapsulationAjouterSommet() {
		RST.ajouter(J, 0);
		J.translater(.5, 3.5);
		memesCoordonnees("E9 : Translater un point ajouté comme sommet "
				+ "ne devrait pas modifier le polygone",
				new Point(1, 1), RST.getSommet(0));
	}

	private void verifierCoordonneesRST() {
		String message = "E9 : Modifier le tableau qui a servi à "
			+ "créer le polygone ne devrait pas modifier le polygone";
		memesCoordonnees(message, new Point(2, -1), RST.getSommet(0));
		memesCoordonnees(message, new Point(5, -1), RST.getSommet(1));
		memesCoordonnees(message, new Point(4, 3), RST.getSommet(2));
	}

	@Test public void testerConstructeurTableau() {
		Point[] tab = { R, S, T };
		RST = new Polygone(tab);
		tab[0] = A;
		verifierCoordonneesRST();
	}

	@Test public void testerConstructeurCouleurTableau() {
		Point[] tab = { R, S, T };
		RST = new Polygone(java.awt.Color.red, tab);
		tab[0] = A;
		verifierCoordonneesRST();
	}




	@Test public void testerAjouterBeaucoup() throws Exception {
		Polygone p = new Polygone(R, S, T);
		java.lang.reflect.Field s = null;
		for (java.lang.reflect.Field f : Polygone.class.getDeclaredFields())
		{
			if (f.getType().equals(Point[].class)) {
				s = f;
				break;
			}
		}
		assertNotNull("Pas d'attribut de type Point[]", s);
		s.setAccessible(true);
		Object o = s.get(p);
		int capacite = java.lang.reflect.Array.getLength(o);
		for (int i = 0; i < capacite; i++) {
			Point n = new Point(-i, -2*i);
			try {
				p.ajouter(n, 0);
			} catch (Exception e) {
				fail("Impossible d'ajouter d'ajouter un sommet "
						+ "à un polygone d'ordre " + (3 + i));
			}
			assertEquals("Ordre incorrect", 4 + i, p.getOrdre());
			memesCoordonnees("Sommet 0 incorrect", n, p.getSommet(0));
		}
	}

	/** Vérifier que deux points ont mêmes coordonnées.
	  * @param p1 le premier point
	  * @param p2 le deuxième point
	  */
	static void memesCoordonnees(Point p1, Point p2) {
		assertEquals(p1.getX(), p2.getX(), EPSILON);
		assertEquals(p1.getY(), p2.getY(), EPSILON);
	}

	/** Vérifier que deux points ont mêmes coordonnées.
	  * @param message le message à utiliser
	  * @param p1 le premier point
	  * @param p2 le deuxième point
	  */
	static void memesCoordonnees(String message, Point p1, Point p2) {
		assertEquals(message + " (abscisses différentes)", p1.getX(), p2.getX(), EPSILON);
		assertEquals(message + " (ordonnées différentes)", p1.getY(), p2.getY(), EPSILON);
	}

	public static void main(String[] args) {
		org.junit.runner.JUnitCore.main(SujetPolygoneTest.class.getName());
	}

}
