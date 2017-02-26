
/** Construire le schéma proposé dans le sujet de TP avec des points,
  * et des segments.
  *
  * @author	Xavier Crégut
  * @version	$Revision: 1.7 $
  */

import afficheur.Afficheur;
import afficheur.Ecran;
import afficheur.AfficheurSVG;

public class ExempleSchema1 {
    
	static Point p1 = new Point(3, 2);
	static Point p2 = new Point(6, 9);
	static Point p3 = new Point(11, 4);
	static Segment s12 = new Segment(p1, p2);
	static Segment s23 = new Segment(p2, p3);
	static Segment s31 = new Segment(p3, p1);

	// Créer le barycentre
	static double sx = p1.getX() + p2.getX() + p3.getX();
	static double sy = p1.getY() + p2.getY() + p3.getY();
	static Point barycentre = new Point(sx / 3, sy / 3);

    /** Affiche le schema et le dessine
      * @param afficheur afficheur dans lequel dessiner le schema
      */
    private static void afficherSchema(Afficheur afficheur){
		//Affiche le schema
        System.out.println("Le schéma est composé de : ");
		s12.afficher();		System.out.println();
		s23.afficher();		System.out.println();
		s31.afficher();		System.out.println();
		barycentre.afficher();	System.out.println();
        
        s12.dessiner(afficheur);
        s23.dessiner(afficheur);
        s31.dessiner(afficheur);
        barycentre.dessiner(afficheur);
    }

	/** Construire le schéma et le manipuler.
	  * Le schéma est affiché.
	  * @param args les arguments de la ligne de commande
	  */
	public static void main(String[] args)
	{
        //Affiche le schema
        Ecran ecran = new Ecran("Joli triangle", 600, 400, 20);
        ecran.dessinerAxes();
        AfficheurSVG svg = new AfficheurSVG("Joli triangle", "Un triangle en SVG", 600, 400);
        String fichierSortie = "schema.svg";
        
        afficherSchema(ecran);
        afficherSchema(svg);
        
        //Translation du schema
        s12.translater(4, -3);
        s23.translater(4, -3);
        s31.translater(4, -3);
        barycentre.translater(4, -3);

        //Redessiner le schema
        afficherSchema(ecran);
        afficherSchema(svg);
        
        //Stockage du svg
        svg.ecrire();
        svg.ecrire(fichierSortie);

	}

}
