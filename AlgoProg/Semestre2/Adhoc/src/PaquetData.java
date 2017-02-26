
public class PaquetData implements Paquet {
	
	/** Le message contenu dans le paquet */
	private Message message;
	/** Le noeud source */
	private String adresseIP;
	/** la route qui mènent vers la destination */
	private Route destination;
	/** Noeud de destination */
	
	public PaquetData (Message Mess, String IP, Route dest) {
		message = Mess;
		adresseIP = IP;
		destination = dest;
	}
	
	/**
	 * @return la route vers la destination
	 */
	public Route getRoute() {
		return destination;
	}

	
	/**
	 * @return le message contenu dans le paquet
	 */
	public Message getMessage() {
		return message;
	}
	
	/**
	 * @return l'adresse du noeud source
	 */
	public String getIPSource() {
		return adresseIP;
	}
	
	/**
	 * @return la taille du paquet
	 */
	public int getTaille() {
		return message.getTaille() + destination.tailleRoute() + 8;
	}
	
	public void transitionPaquet() {
		destination.removeNoeud();
	}
}
