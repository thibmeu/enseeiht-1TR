/** Un ensemble d'entiers implanté en utilisant un tableau.
  * Les nouveaux éléments sont ajoutés à la fin du tableau sauf dans le cas où
  * ils sont déjà présents dans l'ensemble (donc dans le tableau).
  * @author	Xavier Crégut	(cregut@enseeiht.fr)
  * @version	$Revision: 1.7 $
  i*/

import java.util.List;
import java.util.ArrayList;

public class EnsembleTabMin implements Ensemble {
	// Remarque : Un invariant peut être défini « private ».  Il doit
	// l'être s'il porte sur des éléments private de la classe.  Il ne
	// peut alors pas être vérifié par un utilisateur de l'ensemble.
	// Il traduit donc un choix d'implantation et non une
	// spécification de l'ensemble !

	//@ private invariant elements != null;	// le tableau existe
	//@ private invariant cardinal() == nb;	// nb est le cardinal

	// Tous les éléments compris dans les indices [0..cardinal()[
	// du tableau sont dans l'ensemble.
	// -------------------------------------------------------------
	//@ private invariant (\forall int i;
	//@	0 <= i && i < cardinal(); contient(elements[i]));

	// Deux éléments a des indices différents sont différents (les
	// doubles ne sont pas stockés !).
	// -----------------------------------------------------------
	//@ private invariant (\forall int i; 0 <= i && i < cardinal();
	//@	(\forall int j; 0 <= j && j < i;
	//@		elements[i] != elements[j]));

	// Définition du min (vérifiable par JML)
	// --------------------------------------
	//@ private invariant !estVide() ==>
	//@	getMin() == (\min int i;
	//@		0 <= i && i < cardinal(); elements[i]);

	private List<Integer> elements;	// stockage des éléments de l'ensemble

	/** Construction d'un ensemble avec une capacité initiale.
	  * @param capaciteInitiale capacité initiale de l'ensemble */
	//@ requires capaciteInitiale > 0;
	//@ ensures cardinal() == 0;
	public EnsembleTabMin(int capaciteInitiale) {
		elements = new ArrayList<Integer>();
	}

	public int cardinal() {
		return elements.size();
	}

	public boolean estVide() {
		return elements.isEmpty();
	}
	

	public boolean contient(int x) {
        return elements.contains(x);
	}
	
	public void supprimer(int x) {
	    elements.remove(x);
    }

	public void ajouter(int x) {
        Integer[] curTab = new Integer[elements.size()];
        curTab = elements.toArray(curTab);
	    for (int iElement = 0; iElement < curTab.length; iElement++){
            if (x < curTab[iElement]){
                elements.add(iElement, x);
                break;
            }
            else if (iElement == curTab.length-1){
                elements.add(curTab.length, x);
            }
        }
    }

	
	public int getMin() {
        return elements.get(0);
	}

}
