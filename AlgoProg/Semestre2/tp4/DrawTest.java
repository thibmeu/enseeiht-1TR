import afficheur.Ecran;
import java.awt.Color;

public class DrawTest{
    public static void main(String[] argv){
        System.out.println(42);

        Ecran ecran = new Ecran("TestAfficheur", 400, 250, 15);
        ecran.dessinerAxes();
        ecran.dessinerPoint(1, 2, Color.green);
        ecran.dessinerLigne(6, 2, 11, 9, Color.red);
        ecran.dessinerCercle(4, 4, 2.5, Color.yellow);
        ecran.dessinerTexte(1, -2, "Premier texte", Color.blue);
    }
}
