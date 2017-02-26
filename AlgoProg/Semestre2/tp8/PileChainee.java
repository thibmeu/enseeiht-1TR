/** Réalisation de la pile en utilisant un chaînage entre les éléments.
  * @author	Xavier Crégut
  */
public class PileChainee<E> implements Pile<E> {
    
    Cellule<E> pile;
	/** Construire une pile vide. */
	//@ ensures this.estVide();
	public PileChainee() {
		pile = null;
	}

	public boolean estVide() {
		return pile == null; // TODO
	}

	public E sommet() {
        return pile.getElement(); // TODO
	}

	public void empiler(E x) {
		pile = new Cellule<E>(x, pile);
	}

	public void depiler() {
		pile = pile.getSuivante();
	}

}
