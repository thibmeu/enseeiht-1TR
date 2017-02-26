package afficheur;
import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JComponent;

public class AfficheurGraphics extends JComponent {
	
	final static private char NL = '\n';
	final private StringBuilder contenu;
	private Graphics graphe;
	
public AfficheurGraphics(String titre, String description) {
		
		super();
		this.contenu = new StringBuilder();
		this.contenu.append("\t<title>" + titre + "</title>" + NL);
		this.contenu.append("\t<desc>" + description + "</desc>" + NL);
	}
public AfficheurGraphics() {
	this("Carte","La carte du reseau");
}

protected void paintComponent (Graphics g)
{
    super.paintComponent(g);

    g.drawString ("Voici la carte !", 50, 50);
    // Largeur et hauteur du panneau
    int width = getWidth();	
    int height = getHeight(); 
    // Dessin d'une ligne en diagonale
    g.drawLine(width/4, height/4, 3*width/4, 3*height/4);
    // Dessin d'un polygone 
    Point [] points;
    g.drawRect(12, 12, 100, 100);
   // On declare les coordonnées
    // polygone
    // g, x1, y1, x2, y2, ...
    this.dessinerPoly(g,10,10,120,220,40,300);
 // largeur =334 hauteur = 189
    // point plein
    this.dessinerPoint(5*width/6, 5*height/6, 10, g); 
    }

public void dessinerPoly (Graphics g, int... args) {

double x = 0;
double y = 0;

int xpoints[] = new int[6];
int ypoints[] = new int[6];
int npoints = (args.length)/2;

	for (int i = 0; i < args.length; i+=2) {
	 xpoints[i/2] = args[i];
	 System.out.println("x("+i/2+"="+xpoints[i/2]);
	}
	for (int j = 1; j < args.length; j+=2) {
		 ypoints[(j-1)/2] = args[j];
		 System.out.println("y("+j/2+"="+ypoints[j/2]);
		}
	g.drawPolygon(xpoints, ypoints, npoints);
	
}


public void dessinerPoint (int x, int y, int diametre, Graphics g) {
	g.fillOval(x, y, diametre, diametre);
}

public void dessinerPointCreux (int x, int y, int diametre, Graphics g) {
	g.drawOval(x, y, diametre, diametre);
}

/* fonctions existantes dans Graphics :
 * drawLine
drawRect
drawRoundRect
drawOval
drawArc
drawPolyline
drawPolygon
fillRect
fillRoundRect
fillOval
fillArc
fillPolygon*/
}
