import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

/** JeuCartes définit un jeu de cartes avec plusieurs de familles de cartes,
  * avec pour chaque famille le même nombre de cartes.
  * @param <C> type des cartes du jeu
  */
public class JeuCartes<C> implements Iterable<C> {
	private List<C> cartes;

	protected JeuCartes() {
		cartes = new ArrayList<C>();
	}
	
	protected void ajouter(C c) {
		cartes.add(c);
	}
	
	//@ pure
	public String toString() {
		return String.valueOf(this.cartes);
	}

	public void battre() {
		Collections.shuffle(cartes);
	}

	@Override public Iterator<C> iterator() {
		return cartes.iterator();
	}

}
