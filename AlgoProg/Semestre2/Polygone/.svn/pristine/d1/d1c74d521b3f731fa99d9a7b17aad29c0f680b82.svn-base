import java.awt.Color;
import org.junit.*;
import static org.junit.Assert.*;

/** Classe de test pour la robustesse de la classe Polygone.
  * @author	Xavier Crégut <Prenom.Nom@enseeiht.fr>
  */

public class RobustessePolygoneTest {

	protected Polygone p1;
	protected Point a, b, c, d;

	@Before public void setUp() {
		this.a = new Point(2, 0); 
		this.b = new Point(0, 2); 
		this.c = new Point(-2, 0); 
		this.d = new Point(0, -2); 
		this.p1 = new Polygone(Color.RED, a, b, c);
	}


	@Test
	public void testerOptionEnableAssertion() {
		try {
			assert false;
		} catch (AssertionError e) {
			// C'est normal !
			return;
		} catch (Throwable e) {
			// C'est pas normal !
		}
		fail("Il faut exécuter avec l'option -ea de java !");
	}

	@Test(expected=AssertionError.class)
	public void testerGetSommetNegatif() {
		p1.getSommet(-1);
	}

	@Test(expected=AssertionError.class)
	public void testerGetSommetTropGrand() {
		p1.getSommet(3);
	}

	@Test(expected=AssertionError.class)
	public void testerGetSommetPolygoneOrdre0() {
		new Polygone(Color.BLUE).getSommet(0);
	}

	@Test(expected=AssertionError.class)
	public void testerSetCouleur() {
		this.p1.setCouleur(null);
	}

	@Test(expected=AssertionError.class)
	public void testerCreerCouleurNull() {
		new Polygone((Color) null, a, b, c);
	}

	@Test(expected=AssertionError.class)
	public void testerCreerSommetNull0() {
		new Polygone(Color.RED, null, b, c);
	}

	@Test(expected=AssertionError.class)
	public void testerCreerSommetNull1() {
		new Polygone(Color.RED, a, null, c);
	}

	@Test(expected=AssertionError.class)
	public void testerCreerSommetNull2() {
		new Polygone(Color.RED, a, b, null);
	}

	@Test(expected=AssertionError.class)
	public void testerAjouterSommetNull() {
		this.p1.ajouter(null, 0);
	}

	@Test(expected=AssertionError.class)
	public void testerAjouterSommetNullFin() {
		this.p1.ajouter(null);
	}

	@Test(expected=AssertionError.class)
	public void testerAjouterSommetIndiceNegatif() {
		this.p1.ajouter(d, -1);
	}

	@Test(expected=AssertionError.class)
	public void testerAjouterSommetIndiceTropGrand() {
		this.p1.ajouter(d, 4);
	}

	public static void main(String[] args) {
		org.junit.runner.JUnitCore.main(RobustessePolygoneTest.class.getName());
	}

}
