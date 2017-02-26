/** Définit la structure de données Pile.
  * @author	Xavier Crégut
  */
public interface Pile<E> {

	/** Savoir si la pile est vide.
	 * @return vrai si la pile est vide
	 */
	//@ pure
	boolean estVide();

	/** Obtenir l'élément en sommet de la pile.
	  * @return l'élément en sommet de pile
	  */
	//@ requires ! this.estVide();
	//@ pure
	E sommet();

	/** Ajouter un élément au sommet de la pile.
	 * @param x élément à empiler
	 */
	//@ ensures this.sommet() == x;
	void empiler(E x);

	/** Supprimer l'élément en sommet de la pile.  */
	//@ requires ! this.estVide() ;
	void depiler();

}
