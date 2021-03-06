/** Cette classe permet de gérer les route entre différent noeud
 * une route est une suite de noeud
 * @author LAMINE Abdelmalek
 * @version 1.0
 */

import java.util.ArrayList;
import java.util.List;


public class Route {
	
	
	/** Liste d'adresse IP (Chaque noeud a une adresse IP) */
	private List<String> route = new ArrayList<String>();
	
	
    /** Ajoute un noeud a la fin de la Route
     * @param noeud noeud a ajouter
     */
    public void addNoeud(String IP) {
        route.add(IP);
    }
    
    
    /**
     * @return la taille de la route en nombre de bit
     */
    
    public int tailleRoute() {
    	return route.size() * 4; //taille totalement arbitraire
    }
    
    public void removeNoeud() {
    	route.remove(0);
    }
}
