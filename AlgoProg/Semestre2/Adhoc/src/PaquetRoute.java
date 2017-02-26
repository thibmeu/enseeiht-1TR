
/**
 * Classe qui gere les paquet de demande de route et la reponse de demande de route
 * @author Abdelmalek LAMINE
 *
 */


public class PaquetRoute implements Paquet {
	
	/** Noeud Source */
	private String adresseIPSource;
	/** Noeud  destination */
	private String adresseIPDest;
	/** Identifiant unique par du paquet de demande de route */
	private int identifiant;
	/** Route */
	private Route route = new Route();
	/** Vaut true si c'est un paquet de reponse de demande route */
	private boolean reponse;
	/** Reponse de demande de route */
	private Route routeReply;
	
	/**
	 * Constructeur d'un paquet de demande de route
	 * @param IPDest Noeud destination
	 * @param Lidentifiant identifiant unique du paquet de demande de route
	 */
	public PaquetRoute(String IPSource, String IPDest, int Lidentifiant) {
		adresseIPSource = IPSource;
		adresseIPDest = IPDest;
		identifiant = Lidentifiant;
		reponse = false;
	}
	/**
	 * Constructeur d'un paquet de demande de route qui fait office d'une reponse de demande de route initié par un autre noeud
	 * @param IPDest
	 * @param Lidentifiant
	 * @param reponseRoute
	 */
	public PaquetRoute(String IPSource, String IPDest, int Lidentifiant, Route reponseRoute) {
		adresseIPSource = IPSource;
		adresseIPDest = IPDest;
		identifiant = Lidentifiant;
		reponse = true;
		routeReply = reponseRoute;
	}
	
	/**
	 * @return la taille du paquet
	 */
	public int getTaille() {
		return 16 + route.tailleRoute() + routeReply.tailleRoute();   //taille arbitraire pour donner un ordre de grandeur
	}
	
	public boolean routeReply() {
		return reponse;
	}
	
	/***
	 * @return la route
	 */
	public Route getRoute() {
		return route;
	}
	
	/**
	 * Permet d'ajouter un noeud a la route
	 * @param IP le nouveau noeud
	 */
	public void addNoeud(String IP) {
		route.addNoeud(IP);
	}
	
	public int getIdentifiant() {
		return identifiant;
	}
	
	public String getSource() {
		return adresseIPSource;
	}

	public String getDestination() {
		return adresseIPDest;
	}

}
