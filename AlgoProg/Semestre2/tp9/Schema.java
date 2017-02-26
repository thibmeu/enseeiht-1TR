import java.util.ArrayList;

public class Schema {
    ArrayList<ObjetGeometrique> element = new ArrayList<ObjetGeometrique>();
    
    public Schema(ObjetGeometrique... element) {
        for (ObjetGeometrique curElement : element){
            this.element.add(curElement);
        }
    }
    
    public void translater(double dx, double dy) {
        for (ObjetGeometrique curElement : element) {
            curElement.translater(dx, dy);
        }
    }

    public void afficher() {
        for (ObjetGeometrique curElement : element) {
            curElement.afficher();
            System.out.println();
        }
    }

    public void dessiner(afficheur.Afficheur afficheur) {
        for (ObjetGeometrique curElement : element) {
            curElement.dessiner(afficheur);
        }
    }
}
