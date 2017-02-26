import static org.junit.Assert.*;

import java.awt.Color;

import org.junit.Before;
import org.junit.Test;

/**
 * Tests permettant de verifier les exigences et contraintes exprimees dans le
 * sujet.
 *
 * @author	Thibault Meunier
 * @version	2
 */
public class CreerRectangleTest {
	// precision pour les comparaisons entre nombres reels
	public final static double EPSILON = 0.001;
	
	private Point a, b, c, d;
	private Point verifA, verifB, verifC, verifD;
	private Polygone rectangle1, rectangle2, rectangle3, rectangle4, rectangle5;
	Polygone abcd;
	
	@Before public void setUp(){
		a = new Point(0, 0);
		b = new Point(2, 0);
		c = new Point(2, 1);
		d = new Point(0, 1);
		
		verifA = new Point(0, 0);
		verifB = new Point(2, 0);
		verifC = new Point(2, 1);
		verifD = new Point(0, 1);
		
		abcd = new Polygone(verifA, verifB, verifC, verifD);
		
		rectangle1 = Polygone.creerRectangle(a, c);
		rectangle3 = Polygone.creerRectangle(c, a);
		rectangle4 = Polygone.creerRectangle(d, b);
		rectangle5 = Polygone.creerRectangle(b, d);
	}
	
	static void memesCoordonnees(Point p1, Point p2) {
		assertEquals(p1.getX(), p2.getX(), EPSILON);
		assertEquals(p1.getY(), p2.getY(), EPSILON);
	}
    
    static void memesPolygones(Polygone a, Polygone b) {
        assertEquals(a.getOrdre(), b.getOrdre());
        for (int iPoint = 0; iPoint < a.getOrdre(); iPoint++)
            memesCoordonnees(a.getSommet(iPoint), b.getSommet(iPoint));
    }

	@Test public void testerCouleur(){
		assertEquals(rectangle1.getSommet(0).getCouleur(), Color.green);
		rectangle1.getSommet(0).setCouleur(Color.pink);
		assertEquals(rectangle1.getSommet(0).getCouleur(), Color.green);
		b.setCouleur(Color.magenta);
		assertEquals(rectangle1.getSommet(0).getCouleur(), Color.green);
	}
	
	@Test public void testerOrdre(){
		assertEquals("Il manque des points au rectangle", rectangle1.getOrdre(), abcd.getOrdre());
		assertEquals("Il manque des points au rectangle", rectangle1.getOrdre(), 4);
	}
	
	@Test public void testerVraisSommets() {
        memesPolygones(rectangle1, abcd);
        memesPolygones(rectangle3, abcd);
        memesPolygones(rectangle4, abcd);
        memesPolygones(rectangle5, abcd);
	}
	
	@Test public void testerEncapsulation1() {
		memesCoordonnees(verifA, a);
		memesCoordonnees(verifB, b);
		memesCoordonnees(verifC, c);
		memesCoordonnees(verifD, d);
	}
	
	@Test public void testerEncapsulation2() {
	    a.translater(1, 1);
	    b.translater(1, 1);
	    c.translater(1, 1);
	    d.translater(1, 1);
        memesPolygones(rectangle1, abcd);
    }
	
	@Test public void testerDirecticite() {
		assertTrue("Probleme de sens", rectangle1.getSommet(0).getX() < rectangle1.getSommet(1).getX());
		assertTrue("Probleme de sens", rectangle1.getSommet(1).getY() < rectangle1.getSommet(2).getY());
		assertTrue("Probleme de sens", rectangle1.getSommet(2).getX() > rectangle1.getSommet(3).getX());
		assertTrue("Probleme de sens", rectangle1.getSommet(3).getY() > rectangle1.getSommet(0).getY());
	}
	
	@Test(expected=AssertionError.class)
	public void testerSommetNuls1() {
		Polygone.creerRectangle(null, b);
	}
	
	@Test(expected=AssertionError.class)
	public void testerSommetNuls2() {
		Polygone.creerRectangle(d, null);
	}
	
	@Test(expected=AssertionError.class)
	public void testerRectangleLigne() {
		Polygone.creerRectangle(a, b);
	}
	
	@Test(expected=AssertionError.class)
	public void testerRectangleColonne() {
		Polygone.creerRectangle(d, a);
	}
	
	@Test(expected=AssertionError.class)
	public void testerPoint() {
		Polygone.creerRectangle(a, a);
	}
	
	public static void main(String[] args) {
		org.junit.runner.JUnitCore.main(CreerRectangleTest.class.getName());
	}
	
}
