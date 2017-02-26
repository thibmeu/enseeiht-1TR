/** 
 * @author LAMINE Abdelmalek
 * @version 1.0
 */
 

import java.util.*;

public class Noeud {
	
	
	/** Position du noeud*/
	private Position position;
	/** Portée du noeud*/
	private int portee;
	/** Debit maximum du noeud*/
	private int debit; // ???
	/** Liste des paquet en transition par le noeud*/
	private List<Paquet> paquetAttente = new ArrayList<Paquet>();
	/** Nom du noeud*/
	private String IP;
	/** Table de routage du noeud contenant toute les adresse connu*/
	private TableRoute tableRoutage;
	/** Le reseau dans lequel se trouve le noeud */
	private Reseau reseau;
	/** Table de demande de route */
	private List<Paquet> tableDemandeRoute = new ArrayList<Paquet>();
	
	
	public Noeud(String adresseIP, int laPortee, int leDebit, Reseau leReseau, double abscisse, double ordonne ) {
		position = new Position(abscisse, ordonne);
		portee = laPortee;
		debit = leDebit;
		tableRoutage = new TableRoute();
		reseau = leReseau;
	}
	
	/**
	 * @return la portee du noeud
	 */
	public int getPortee() {
		return portee;
	}
	
	
	/**
	 * Fonction qui permet de modifier la position du noeud
	 */
	public void setPosition(Position nouvellePosition) {
		position = nouvellePosition;
	}
	
	/**
	 * @return la position du noeud
	 */
	public Position getPosition() {
		return position;
	}
	
	
	
	/** Fonction qui permet d'initier une demande de route vers un autre
	 * noeud du réseaux.
	 * @param E un autre noeud du réseaux
	 */
	public void demandeRoute(String IPDest) {
		reseau.getProtocole().demandeRoute(this.IP, IPDest);
	}
	
	/** Fonction qui permet d'envoyer un paquet a tous les noeuds du réseaux qui sont a porté.
	 * Si aucun noeud n'est a porté, le paquet reste en attente.
	 * @param p le paquet a envoyer
	 */
	public void envoyerPaquet(Paquet lePaquet) {
		boolean acquitement = reseau.getProtocole().envoyerPaquet(IP, lePaquet);
		if (! acquitement) {
			paquetAttente.add(lePaquet);
		}
	}
	
	public void envoyerPaquet(Message leMessage, String IPDest) {   
		if (existeRoute(IPDest)) {
			Paquet toSend = new PaquetData(leMessage, IP, tableRoutage.getRoute(IPDest));
			this.envoyerPaquet(toSend);
		}
		
		else {
			this.demandeRoute(IPDest);
		}
	}
	

	private boolean existeRoute(String IPDest) {
		return tableRoutage.nombreRouteExistance(IPDest) > 0;
	}
	
}	
	
	
