import java.awt.Color;

public abstract class ObjetGeometrique {
    Color color;
    
    public ObjetGeometrique(Color color) {
        setCouleur(color);
    }
    
    final public Color getCouleur() {
        return color;
    }

    final public void setCouleur(Color color) {
        this.color = color;
    }

    abstract void translater(double dx, double dy);

    abstract void afficher();

    abstract void dessiner(afficheur.Afficheur afficheur);
}
