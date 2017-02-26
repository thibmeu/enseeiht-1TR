import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

/**
 * Tests permettant de vérifier les exigences et contraintes exprimées dans le
 * sujet.
 *
 * @author	Thibault Meunier
 * @version	1
 */
public class PolygoneTest {
	
	// précision pour les comparaisons entre nombres réels
		public final static double EPSILON = 0.001;
		
		private Point a, b, c, d;
		private Polygone a0, ab, abc, abcd;
	
		@Before public void setUp(){
		a = new Point(0, 0);
		b = new Point(2, 0);
		c = new Point(2, 1);
		d = new Point(0, 1);
		a0 = new Polygone(a);
		ab = new Polygone(a, b);
		abc = new Polygone(a, b, c);
		abcd = new Polygone(a, b, c, d);
	}
	
	@Test public void testPerimetre() {
		//Polygone d'ordre 1
		assertEquals("Probleme de perimetre pour un point", a0.perimetre(), 0, EPSILON);
		
		//Polygone d'ordre 2
		assertEquals("Probleme de perimetre pour un segment", ab.perimetre(), 4, EPSILON);
		
		//Polygone d'ordre 3
		assertEquals("Probleme de perimetre pour un triangle", abc.perimetre(), 2+1+Math.sqrt(5), EPSILON);
		
		//Polygone d'ordre 4
		assertEquals("Probleme de perimetre pour un quadrilatere", abcd.perimetre(), 6, EPSILON);
	}
	
	public static void main(String[] args) {
		org.junit.runner.JUnitCore.main(PolygoneTest.class.getName());
	}
	
}
