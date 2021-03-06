/** Table de routage
 * @author LAMINE Abdelmalek
 * @version 1.0
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class TableRoute {
	
	
	private Map<String, List<Route>> routes = new HashMap<String, List<Route>>();
	
	
	/** Fonction qui permet d'ajouter une nouvelle route a la table de routage */
	public void addRoute(Route route, String IP) {
		if (! routes.containsKey(IP)) {
			routes.put(IP, new ArrayList<Route>());
		}
		routes.get(IP).add(route);
	}
	
	public int nombreRouteExistance(String IP) {
		int nombre = 0;
		if (routes.containsKey(IP)) {
			nombre = routes.get(IP).size();
		}
		return nombre;
	}
	
	
	/**
	 * @param IP Le nom du noeud
	 * @return La route vers le noeud dont le nom est IP
	 */
	
	public Route getRoute(String IP) {
		return routes.get(IP).get(0);
	}

	
	/**
	 * @param IP
	 * @return true si le noeud existe dans la table de routage
	 */
	
	public boolean existeRoute(String IP) {
		return routes.containsKey(IP);
	}

	
	/** 
	 * Fonction qui permet de supprimer une route
	 */
	public void deleteRoute(String IP) {
		if (existeRoute(IP)) {
			routes.get(IP).remove(0);
		}
	}
	
	
}
