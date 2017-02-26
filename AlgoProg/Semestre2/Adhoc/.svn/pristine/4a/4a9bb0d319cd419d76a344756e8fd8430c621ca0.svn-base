/**
 * @author LAMINE Abdelmalek
 * @version 1.0
 */

public class Message {
	
	private String message;
	
	
	/**
	 * @param mess Le message qu'on veut envoyer
	 */
	public Message(String mess) {
		this.message = mess;
	}
	
	
	/** Fonction qui permet de récupérer le message
	 * @return le message
	 */
	public String getMessage() {
		return this.message;
	}
	
	/**Fonction qui définit la taille d'un message en nombre de bit
	 * La taille ici est indicatif et n'est pas égale a la taille réelle de la chaine de caractere
	 * @return la taille du message
	 */
	public int getTaille() {
		int resultat = message.length() * 8; //on considere que chaque caractere est "codé" sur 8 bit
		return resultat;
	}
	

}
