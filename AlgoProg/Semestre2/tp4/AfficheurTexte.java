import java.awt.Color;
import afficheur.Afficheur;

public class AfficheurTexte implements Afficheur{
    public void dessinerPoint(double x, double y, Color color){
        System.out.println("Point {");
        System.out.println("x = " + x);
        System.out.println("y = " + y);
        System.out.println(color);
        System.out.println("}");
    }

    public void dessinerLigne(double x1, double y1, double x2, double y2, Color color){
        System.out.println("Ligne {");
        System.out.println("x1 = " + x1);
        System.out.println("y1 = " + y1);
        System.out.println("x2 = " + x2);
        System.out.println("y2 = " + y2);
        System.out.println(color);
        System.out.println("}");
    }

    public void dessinerCercle(double x, double y, double rayon, Color color){
        System.out.println("Cercle {");
        System.out.println("centre_x = " + x);
        System.out.println("centre_y = " + y);
        System.out.println("rayon = " + rayon);
        System.out.println(color);
        System.out.println("}");
    }

    public void dessinerTexte(double x, double y, String texte, Color color){
        System.out.println("Texte {");
        System.out.println("x = " + x);
        System.out.println("y = " + y);
        System.out.println("valeur = " + texte);
        System.out.println(color);
        System.out.println("}");
    }
}
