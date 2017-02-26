import java.util.*;
/**
 * 
 * @author Driouich Ilias
 * @version 1.0
 */
public class Reseau  {
	
	private Map<String, Noeud> noeuds;
	
	private Protocole protocole;
	
	
	
	public Reseau(Protocole leProtocole) {
		noeuds = new HashMap<String, Noeud>();
		protocole = leProtocole;
	}
	
	public Noeud getNoeud(String IP){
		return noeuds.get(IP);
		
	}

    public void addNoeud(Noeud noeud, String IP){
		noeuds.put(IP, noeud);
	}

    public void removeNoeud(String IP){
		noeuds.remove(IP);
	}

    public void pauseNoeud(String IP){
		
	}

    public void wakeNoeud(String IP){
		
	}

    public void envoiePaquet(String IP){
		
	}
    
    public Protocole getProtocole() {
    	return protocole;
    }
    
    public int getNouveauIdDemandeRoute() {
    	identifiant +=1;
    	return identifiant - 1;
    }
	
}
