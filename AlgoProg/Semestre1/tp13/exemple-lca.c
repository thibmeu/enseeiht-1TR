/*******************************************************************************
 *  Auteur   : 
 *  Objectif : Un exemple d'utilisation d'une LCA.
 ******************************************************************************/
#define TYPE_LCA 1
#define TYPE_TH 2
#define TYPE_TABLE TYPE_LCA

#include <stdio.h>
#include <assert.h>
#include "lca.h"
#if TYPE_TABLE == TYPE_TH
#include "fonctions-hachage.h"
#endif

int main() {
    LCA dict;
#if TYPE_TABLE == TYPE_LCA
    // Initialiser dict comme une LCA.
    init_LCA(&dict);
#else
    // Initialiser dict comme une TH de taille 11 avec la fonction taille.
    init_TH(&dict, 11, taille);
#endif


    char clef[] = "aaa";
    // Enregistrer -1 avec cle dans dict.
    add_LCA(&dict, clef, -1);
    // Vérifier que clef est une clef utilisée
    assert(has_key_LCA(dict, clef));
    // Vérifier que la valeur de clef est -1
    assert(getValue_LCA(dict, clef) == -1);

    clef[0] = 'b';
    // Enregistrer -2 avec cle dans dict.
    add_LCA(&dict, clef, -2);
    // Vérifier que clef est une clef utilisée
    assert(has_key_LCA(dict, clef));
    // Vérifier que la valeur de clef est -2
    assert(getValue_LCA(dict, clef) == -2);
    // Vérifier que "aaa" est une clef utilisée
    assert(has_key_LCA(dict, "aaa"));
    // Vérifier que la valeur de la clef "aaa" est -1
    assert(getValue_LCA(dict, "aaa") == -1);
	
	printf("Exemple terminé avec succès\n");
}
