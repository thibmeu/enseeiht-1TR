public interface Message {
	/** Obtenir le pseudo de l'utilisateur Ã  l'orgine du message.
	 * @return le pseudo de l'utilisateur Ã  l'origine du message
	 */
	String getPseudo();

	/** Obtenir le texte du message.
	 * @return le texte du message.
	 */
	String getTexte();

	@Override String toString();

}
