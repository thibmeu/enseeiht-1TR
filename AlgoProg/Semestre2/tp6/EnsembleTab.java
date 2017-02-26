/** Un ensemble d'entiers implanté en utilisant un tableau.
  * Les nouveaux éléments sont ajoutés à la fin du tableau sauf dans le cas où
  * ils sont déjà présents dans l'ensemble (donc dans le tableau).
  * @author	Xavier Crégut	(cregut@enseeiht.fr)
  * @version	$Revision: 1.7 $
  i*/

import java.util.Arrays;

public class EnsembleTab implements Ensemble {
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

	private int[] elements;	// stockage des éléments de l'ensemble
	private int nb;	// taille effective de elements

	/** Construction d'un ensemble avec une capacité initiale.
	  * @param capaciteInitiale capacité initiale de l'ensemble */
	//@ requires capaciteInitiale > 0;
	//@ ensures cardinal() == 0;
	public EnsembleTab(int capaciteInitiale) {
		elements = new int[capaciteInitiale];
        nb = 0;
	}

	public int cardinal() {
		return nb;
	}

	public boolean estVide() {
		return nb == 0;
	}
	

	public boolean contient(int x) {
		for (int iElement = 0; iElement < nb; iElement++){
            if (elements[iElement] == x){
                return true;
            }
        }
        return false;
	}
	
	public void supprimer(int x) {
//	    System.out.println("this is " + x);
//        System.out.println(Arrays.toString(elements) + "\nnb = " + nb);
        for (int iElement = 0; iElement < nb; iElement++){
            if (elements[iElement] == x){
                elements[iElement] = elements[nb-1];
                elements = Arrays.copyOf(elements, elements.length - 1);
                nb -= 1;
//                System.out.println(Arrays.toString(elements) + contient(x));
                
                return;
            }
        }
	}

	public void ajouter(int x) {
		if (!contient(x)){
            if (elements.length == nb){
                elements = Arrays.copyOf(elements, elements.length+10);
            }
            elements[nb] = x;
            nb += 1;
        }
	}

	
	public int getMin() {
		int curMin = elements[0];
        for (final int curElement : elements){
            curMin = (curElement < curMin) ? curElement : curMin;
        }
        return curMin;
	}

}
