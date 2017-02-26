/** Une cellule encapsule un élément et un accès
 * à une autre cellule dite suivante.
 */
class Cellule<E> {
	private E element;
	private Cellule<E> suivante;

	//@ ensures this.element == element;
	//@ ensures this.suivante == suivante;
    public Cellule(E element, Cellule<E> suivante) {
		this.element = element;
		this.suivante = suivante;
	}

	public E getElement() {
		return this.element;
	}

	//@ ensures this.element == element;
	public void setElement(E element) {
		this.element = element;
	}

	public Cellule<E> getSuivante() {
		return this.suivante;
	}

	//@ ensures this.suivante == suivante;
	public void setSuivante(Cellule<E> suivante) {
		this.suivante = suivante;
	}

	public String toString() {
		// Attention, il ne faut pas que les cellules forment un cycle !
		return "[" + this.element + "]--"
				+ (this.suivante == null ? 'E' : ">" + this.suivante); 
	}

}
