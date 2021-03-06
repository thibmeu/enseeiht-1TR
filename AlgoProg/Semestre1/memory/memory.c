/*********************************************************************
 **  Auteurs  : Thibault Meunier, Hugo Montal
 **  Objectif : Jouer au jeu du Memory
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define NB_CARTES 52
#define NB_ENSEIGNES 4
#define NB_VALEURS 13
#define NB_COULEURS NB_ENSEIGNES/2
#define NB_ETAPES 2
#define NB_CARTES_ETOURDI 10
#define TAILLE_LIGNE 3
#define TAILLE_COLONNE 6
#define DECALAGE 1
#define MAX_NOM 10+1
#define MIN_JOUEURS 2
#define MAX_JOUEURS 1000
#define NB_LIGNES NB_ENSEIGNES
#define NB_COLONNES NB_VALEURS
#define NB_LIGNES_AFFICHAGE NB_LIGNES*TAILLE_LIGNE+1 + 2*DECALAGE
#define NB_COLONNES_AFFICHAGE NB_COLONNES*TAILLE_COLONNE+1 + 2*DECALAGE
#define NB_ETATS_CARTE 3
#define NB_IA 3
#define NB_TYPES NB_IA+1
#define HAUTEUR_CARTE 2
#define LARGEUR_CARTE 3
#define ABANDON -1


 char txtEnseigne[NB_ENSEIGNES][TAILLE_LIGNE] = {"PIQ", "COE", "CAR", "TFL"};
 char txtValeur[NB_VALEURS][TAILLE_LIGNE] = {"AS ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 ", "10 ", "VLT", "DME", "ROI"};
 char* txtTypes[NB_TYPES] = {"Humain", "Naif", "Expert", "Distrait"};

enum Enseigne {Pique, Coeur, Carreau, Trefle};
typedef enum Enseigne Enseigne;
enum Valeur {As, Deux, Trois, Quatre, Cinq, Six, Sept, Huit, Neuf, Dix, Valet, Dame, Roi};
typedef enum Valeur Valeur;
enum Difficulte{NAIF, EXPERT, ETOURDI};
typedef enum Difficulte Difficulte;
enum EtatCarte {VISIBLE, CACHEE, RETIREE};
typedef enum EtatCarte EtatCarte;

 char affEtatCarte[NB_ETATS_CARTE][TAILLE_LIGNE][TAILLE_COLONNE] =
{{"???", "???"},	//VISIBLE --> INCONNU
    {"~~~", "~~~"},	//CACHEE
    {"   ", "   "}};	// RETIREE


// Debut de la classe Position
struct Position
{
    int ligne;
    int colonne;
};
typedef struct Position Position;

void init_Position( int ligne,  int colonne, Position* this);
/*
 * Procedure init_Position(ligne: Entier in, colonne: Entier in, position: Position out)
 * 
 * Initialise une position a partir des coordonnees
 * 
 * Necessite:
 * ligne < NB_LIGNES
 * colonne < NB_COLONNES
 * this != NULL
 */

 Position memoireVide = {-1, -1};
/*
 * Permet de remplir la memoire de case vide (hors tapis)
 */

void affichage_Position( Position position);
/*
 * Procedure affichage_Position(position: Position in)
 * 
 * Afficher une position sous le format "Ligne :%d - colonne : %d"
 * 
 * Necessite:
 * Position initialisee
 */

bool isEgalesPositions( Position a,  Position b);
/*
 * Fonction isEgalesPositions(a: Position in, b: Position in)
 * 
 * Teste si deux position sont egales
 * 
 * Necessite:
 * a et b deux positions initialisees
 * 
 * Assure:
 * Renvoie 1 si a et b sont identiques, 0 sinon
 */

void setPosition( Position b, Position* this);
/*
 * Procedure setPosition(b: Position in, this: Position out)
 * 
 * Initialise this a partir de b
 * 
 * Necessite:
 * b initialisee
 * this != NULL
 * 
 * Assure:
 * *this <- b
 */
 
// Fin de la classe position

//Debut de la classe Carte
struct Carte
{
    Enseigne enseigne;
    Valeur valeur;
};
typedef struct Carte Carte;

void init_Carte( Enseigne enseigne,  Valeur valeur, Carte* this);
/*
 * Procedure init_Carte(enseigne: Enseigne in, valeur: Valeur in, this: Carte out)
 * 
 * Initialise carte a partir d'une enseigne et d'une valeur
 * 
 * Necessite:
 * enseigne et valeur dans leur enumeration respective
 * this != NULL
 */

bool couleurCarte( Carte c);
/*
 * Fonction couleurCarte(c: Carte in)
 * 
 * Renvoie la couleur de la carte fournie en entree
 * 
 * Necessite:
 * c initialisee
 * 
 * Assure:
 * Renvoie 1 si la couleur de la carte est rouge, 0 sinon
 */


bool isEgalesCartes( Carte c1,  Carte c2);
/*
 * Fonction isEgalesCartes(c1: Carte in, c2: Carte in)
 * 
 * Teste si deux cartes sont egales
 * 
 * Necessite:
 * c1 et c2 initialisees
 * 
 * Assure:
 * Renvoie 1 si c1 et c2 sont identiques, 0 sinon
 * 
 */


bool isPaireCarte( Carte c1,  Carte c2);
/*
 * Fonction isPaireCarte(c1: Carte in, c2: Carte in)
 * 
 * Teste si les deux cartes forment une paire
 * 
 * Necessite:
 * c1 et c2 initialisees
 * 
 * Assure:
 * Renvoie 1 si c1 et c2 forment une paire, 0 sinon
 */

// Fin de la classe Carte

//Debut de la classe Jeu52
typedef Carte Jeu52 [NB_CARTES];

void init_Jeu52(Jeu52 jeu);
/*
 * Procedure init_Jeu52(jeu: Jeu52 out)
 * 
 * Initialise jeu
 * 
 * Necessite:
 * jeu != NULL
 * 
 * Assure:
 * Toutes les cartes d'un jeu de 52 sont dans jeu
 */

void permuter(Jeu52 jeu);
/*
 * Procedure permuter(jeu: Jeu52 in/out)
 * 
 * Choisit deux cartes au hasard (peuvent etre identiques) et les permute
 * 
 * Necessite:
 * jeu initialise
 */


void battre(Jeu52 jeu);
/*
 * Procedure battre(jeu : Jeu52 in/out)
 * 
 * Bat le jeu
 * 
 * Necessite:
 * jeu initialise
 * 
 * Assure:
 * jeu a ete bien battu
 */


void calculPosCartes( Jeu52 jeu, int posCarte[NB_CARTES]);
/*
 * Procedure calculPosCartes(jeu: Jeu52, posCarte: Tableau de [NB_CARTES] Entier)
 * 
 * Determine la position de chaque carte dans le jeu
 * 
 * Necessite:
 * jeu initialise
 * posCarte != NULL
 * 
 * Assure:
 * posCarte rempli avec des valeurs comprises entre 0 et 51 inclu
 */


void affichage( Jeu52 jeu);
/*
 * Procedure affichage(jeu: Jeu52 in)
 * 
 * Affiche la position des cartes dans le jeu battu
 * 
 * Necessite:
 * jeu initialise
 */


bool bienBattu( Jeu52 jeu);
/*
 * Fonction bienBattu(jeu: Jeu52 in)
 * 
 * Teste si le jeu ne presente pas deux cartes consecutives qui le sont dans le jeu ordonne
 * 
 * Necessite:
 * jeu initialise
 * 
 * Assure:
 * Renvoie 1 si le jeu est bien battu, 0 sinon
 */

// Fin de la classe Jeu52

//Debut de la classe CarteReele
struct CarteReele
{
    Carte carte;
    EtatCarte etat;
};
typedef struct CarteReele CarteReele;

void init_CarteReele( Carte carte,  EtatCarte etat, CarteReele* this);
/*
 * Procedure init_CarteReele(carte: Carte in, etat: EtatCarte in, this: CarteReele out)
 * 
 * Initialise this a partir d'une carte et de son etat
 * 
 * Necessite:
 * carte et etat initialises
 * this != NULL
 */

//Fin de la classe CarteReele

//Debut de la classe Tapis
typedef CarteReele Tapis [NB_ENSEIGNES][NB_VALEURS];

void init_Tapis(Tapis tapis);
/*
 * Procedure init_Tapis(tapis: Tapis out)
 * 
 * Initialise tapis en distribuant un jeu de 52 cartes battues
 * 
 * Necessite:
 * tapis != NULL
 * 
 * Assure:
 * Toutes les cases du tapis sont occupees par une carte differente
 */

//Fin de la classe Tapis

//Debut de la classe Joueur
struct Joueur
{
    char nom[MAX_NOM];
    bool humain;
    Difficulte difficulte;//Si le joueur est virtuel vaut NULL
    Position memoire[NB_CARTES]; //initialiser a {-1,-1} == memoire vide
    int score;
};
typedef struct Joueur Joueur;

void init_Joueur( char nom[MAX_NOM],  bool humain,  Difficulte difficulte,  Position memoire[NB_CARTES],  int score, Joueur *joueur);
/*
 * Procedure init_Joueur(nom: Tableau de [MAX_NOM] Caractere in, humain: Booleen in, difficulte: Difficulte in, memoire: Tableau de [NB_CARTES] Position in, score: Entier in, joueur: Joueur out)
 * 
 * Initialise un joueur a partir de ses differentes caracteristiques
 * 
 * Necessite:
 * joueur != NULL
 */
//Fin de la classe Joueur

void trueStrCpy(char str1[],  char str2[],  int taille);
/*
 * Procedure trueStrCpy(str1: Chaine de Caracteres in/out, str2: Chaine de Caracteres in, taille: Entier in)
 * 
 * On copie [taille] caractere de la chaine str2 dans la chaine str1
 * 
 * Necessite:
 * len(str1) >= len(str2) >= taille
 * 
 * Assure:
 * str2 remplace le debut de str1
 */

void clear_stdin();
/*
 * Procedure clear_stdin()
 * 
 * Vide la stdin
 * 
 * Assure:
 * La stdin ne contient plus aucun caractere
 */

void clear();
/*
 * Procedure clear()
 * 
 * Nettoie la fenetre du terminal
 */

bool ppause();
/*
 * Fonction ppause()
 * 
 * Attend jusqu'au prochaine caractere saisi par l'utilisateur
 *
 * Assure :
 * Renvoie Vrai si le caractere saisie est un a/A --> permet d'abandonner
 */

CarteReele* tapisPosition(Tapis tapis,  Position position);
/*
 * Fonction tapisPosition(tapis: Tapis in, position: Position in)
 * 
 * Renvoie la CarteReele du tapis se trouvant a la position
 * 
 * Necessite:
 * tapis initialise
 * position dans le tapis
 * 
 * Assure:
 * Renvoie la CarteReele si la position est valide
 */

bool isDansTapis( Position position);
/*
 * Fonction isDansTapis(position: Position in)
 * 
 * Verifie si une position est dans le tapis
 * 
 * Assure:
 * Renvoie 1 si la position est bien dans le tapis, 0 sinon
 */

bool isDansMemoire( Position memoire[NB_CARTES],  Position position);
/*
 * Fonction isDansMemoire(memoire: Tableau de [NB_CARTES] Position in, position: Position in)
 * 
 * Verifie si une carte (position) est dans la memoire
 * 
 * Assure:
 * Renvoie 1 si la carte est bien dans la memoire, 0 sinon
 */

void stockageMemoireJoueur( Tapis tapis, Position memoire[NB_CARTES],  Position carte,  Difficulte difficulte);
/*
 * Procedure stockageMemoireJoueur(tapis: Tapis in, memoire: Tableau de [NB_CARTES] Position in/out, carte: Position in, difficulte: Difficulte in)
 * 
 * Ajoute la position d'une carte a la memoire d'une joueur selon ses capacites
 * 
 * Necessite:
 * memoire != NULL
 * 
 * Assure:
 * Ne rajoute pas la carte a la memoire si celle ci a deja ete memorisee
 */

void affichage_memoire( Position memoire[NB_CARTES]);
/*
 * Procedure affichage_memoire(memoire: Tableau de [NB_CARTES] Position in)
 * 
 * Affiche le contenu de la memoire d'un joueur
 * 
 * Necessite:
 * memoire != NULL
 */

void memoriseCarte( Tapis tapis, Joueur* joueur,  Position carteRetournee[NB_ETAPES]);
/*
 * Procedure memoriseCarte(tapis: Tapis in, joueur: Joueur in/out, carteRetournee: Tableau de [NB_ETAPES] Position)
 * 
 * Memorise les cartes retournees pendant le tour
 * 
 * Necessite:
 * joueur != NULL
 * carteRetournee != NULL
 * 
 * Assure:
 * Le joueur memorisera la carte si il le peut, et si il ne l'a pas deja en memoire
 */

void affichageTapis( char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE]);
/*
 * Procedure affichageTapis(affTapis: Tableau de [NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE] Caractere in)
 * 
 * Affiche le tapis actuel
 * 
 * Necessite:
 * AffTapis initialise et represantant l'etat du tapis actuel
 * 
 */

void init_affTapis(char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE]);
/*
 * Procedure init_affTapis(affTapis: Tableau de [NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE] Caractere out)
 * 
 * Initialise l'affichage du tapis
 * 
 * Necessite:
 * affTapis != NULL
 * 
 * Assure:
 * Toutes les cartes sont retournees
 */

void lire_nbJoueurs(int* nbJoueurs);
/*
 * Procedure lire_nbJoueurs(nbJoueurs: Tableau de [MAX_NOM] Entier in/out)
 *
 * Initialise nbJoueurs en fonction de l'entree fourni par l'utilisateur
 *
 * Necessite:
 * nom != NULL
 */

int lire_nom(char nom[MAX_NOM]);
/*
 * Procedure lire_nom(nom: Chaine de caracteres out)
 *
 * Initialise nom en fonction de l'entree fourni par l'utilisateur
 *
 * Necessite:
 * nom != NULL
 *
 * Assure:
 * nom est valide
 */

void lire_humain(bool* humain);
/*
 * Procedure lire_humain(humain: Booleen out)
 *
 * Initialise humain en fonction de l'entree fourni par l'utilisateur
 *
 * Necessite:
 * humain != NULL
 *
 * Assure:
 * humain est valide
 */

void lire_difficulte(Difficulte* difficulte,  bool humain);
/*
 * Procedure lire_difficulte(difficulte: Difficulte out, humain: Booleen in)
 *
 * Initialise difficulte en fonction de l'entree fourni par l'utilisateur
 *
 * Necessite:
 * difficulte != NULL
 *
 * Assure:
 * difficulte est valide
 */

void init_tab_joueur(Joueur joueur[MAX_JOUEURS], int* nbJoueurs);
/*
 * Procedure init_tab_joueur(joueur: Tableau de [MAX_JOUEURS] Joueur out, nbJoueurs: Entier out)
 * 
 * Demande a l'utilisateur le nombre de joueur, et effectue leurs initialisations
 * 
 * Necessite:
 * Un controle des donnees entrees par l'utilisateur (taille du nom, mode de jeu, etc...)
 * 
 * Assure:
 * joueur est initialise correctement et peut etre traite sans risque
 */

void initialisation(Tapis tapis, char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], Joueur joueur[MAX_JOUEURS], int* nbJoueurs);
/*
 * Procedure initialisation(tapis: Tapis out, affTapis: Tableau de [NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE] Caractere out, joueur: Tableau de [MAX_JOUEURS] Joueur out, nbJoueurs: Entier out) 
 * 
 * Initialise tous les parametres necessaire au bon deroulement du jeu
 * 
 * Necessite:
 * tapis != NULL
 * affTapis != NULL
 * joueur != NULL
 * nbJoueurs != NULL
 * 
 * Assure:
 * Les differents parametres renvoyes sont utilisables pour une partie de memory
 */

void afficheJoueur( Joueur joueur,  int iClassementJoueur);
/*
 * Procedure afficheJoueur(joueur: Joueur in, iClassementJoueur: Entier in)
 * 
 * Affiche une ligne avec le nom du joueur, son score, et son classement
 * 
 * Necessite:
 * 0 < iClassementJoueur <= nbJoueurs
 */

int compareScore(const void* a, const void* b);
/*
 * Procedure compareScore(a: Joueur in, b: Joueur in)
 * 
 * Compare le score des joueurs a et b et si le joueur b a un score plus grand, il est classé avant le joueur a
 * 
 */

void affichageVainqueurs(Joueur joueur[MAX_JOUEURS], int nbJoueurs);
/*
 * Procedure affichageVainqueurs(joueur: tableau de [MAX_JOUEURS] Joueur in, nbJoueur: Entier in)
 * 
 * Affiche les joueurs dans l'ordre de leur score sous forme de tableau
 * 
 * Necessite:
 * Les scores ont ete initialises
 * 
 */

void placeCarte(char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], char affCarte[HAUTEUR_CARTE][LARGEUR_CARTE], Position position);
/*
 * Procedure placeCarte(affTapis: tableau de [NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE] Caracteres in/out, affCarte: tableau de [HAUTEUR_CARTE][LARGEUR_CARTE] Caractere, position: Poisition)
 * 
 * Place l'affichage de la carte a sa position dans le tapis d'affichage
 * 
 * Necessite:
 * La position correspond a l'affichage de la carte
 * 
 */

void changementCarte(Tapis tapis, char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], Position position, EtatCarte etat);
/*
 * Procedure changementCarte(tapis: Tapis in, affTapis: tableau de [NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE] Caracteres in/out, position: Position in, etat: EtatCarte)
 * 
 * Modifie l'etat de la carte dans le tapis et l'affichage du tapis avec l'etat passe en parametre
 * 
 * Necessite:
 * La carte ne soit pas deja dans l'etat passe en parametre
 * 
 * Assure:
 * La carte a la position donnee a change d'etat
 */

void lecturePosition(Position* position);
/*
 * Procedure lecturePosition(position: Position in/out)
 * 
 * Fourni au joueur humain une interface de saisie de cartes
 * 
 * Assure:
 * La position est celle d'une carte retournee dans le tapis
 */

void cacheMemoire(Tapis tapis, Position memoire[NB_CARTES]);
/*
 * Procedure cacheMemoire(tapis: Tapis in, memoire: tableau de [NB_CARTES] Position in)
 * 
 * Remet le tapis dans sa position d'origine comme si il n'avait pas etait modifie
 * 
 * Assure:
 * Le tapis est dans la position qu'il etait avant la saisie de la position
 */

void ia_memoire(Tapis tapis, int nbCartesRestantes, Position memoire[NB_CARTES], Position cartePrec, Position* position);
/*
 * Procedure ia_memoire(tapis: Tapis in, nbCartesRestantes: Entier in, memoire: tableau de [NB_CARTES] Position in , position: Position in/out)
 * 
 * Gere la saisie d'une carte en fonction de la memoire prise en parametre (expert ou etourdi)
 * 
 * Necessite:
 * La carte precedente soit initialisee
 * 
 * Assure:
 * La position est celle d'une carte retournee dans le tapis
 */

void carteAleatoireCachee(Tapis tapis, int iCarte, Position* position);
/*
 * Procedure carteAleatoireCachee(tapis: Tapis in, iCarte: Entier in, position: Position in/out)
 * 
 * Selection d'une carte retournee dans le tapis en fonction de iCarte genere aleatoirement
 * 
 * Necessite:
 * 0 < iCarte <= au nombre de cartes restantes
 * 
 * Assure:
 * La position est celle d'une carte retournee dans le tapis
 */

void ia_naif(Tapis tapis,  int nbCartesRestantes, Position* position);
/*
 * Procedure ia_naif(tapis: Tapis in, nbCartesRestantes: Entier in, position: Position out)
 * 
 * Gere la saisie d'une carte de l'ia naif
 * 
 * Assure:
 * La position renvoyee est bien dans le tapis
 */

void saisieCarte(Tapis tapis,  Joueur joueur,  int nbCartesRestantes, Position carteRetournee[NB_ETAPES],  int iEtape);
/*
 * Procedure saisieCarte(tapis: Tapis in/out, joueur: Joueur in, nbCartesRestantes: Entier in, carteRetournee: tableau de [NB_ETAPES] Position in/out, iEtape: Entier in)
 * 
 * Gere la saisi d'une carte en fonction du type du joueur
 * 
 * Necessite:
 * La premiere carte est initialisee soit a vide, soit avec une premiere saisie
 * 
 * Assure:
 * Le tableau de position contient 1 ou 2 cartes presente dans le tapis
 */

void choixDesCartes(Tapis tapis, Position carteRetournee[NB_ETAPES], char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE],  Joueur joueur,  int nbCartesRestantes);
/*
 * Procedure choixDesCartes(tapis: Tapis in/out, carteretournee: tableau de [NB_ETAPES] Position in/out ,affTapis: tableau de [NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE] characteres in, joueur: Joueur in , nbCartesRestantes: Entier in)
 * 
 * Coordonne les saisies de cartes
 * 
 * Necessite:
 * Que le joueur existe
 * 
 * Assure:
 * Que les deux cartes retournees existent et sont dans le tapis
 */

void tourJoueur(Tapis tapis, char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], Joueur joueur[MAX_JOUEURS], int nbJoueurs, int *iJoueur, int* nbCartesRestantes);
/*
 * Procedure tourJoueur(tapis: Tapis in/out, affTapis: tableau de [NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE] Caracteres in, joueur: tableau de [MAX_JOUEURS] Joueur in/out, nbJoueur: Entier in, iJoueur: Entier in/out, nbCartesRestantes: Entier in/out)
 * 
 * Realise le tour d'un joueur en coordonnant l'affichage du tapis, la mise en memoire et la modification des cartes dans le tapis
 * 
 * Necessite:
 * Il reste des cartes dans le tapis
 * 
 * Assure:
 * Aucune carte n'est face visible
 */

bool testTapis(int nbCartesRestantes);
/*
 * Test si le tapis est vide
 * 
 * Necessite:
 * Le nombre de carte restante n'est pas négatif
 * 
 */

void partie(Tapis tapis, char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], Joueur joueur[MAX_JOUEURS], int nbJoueurs);
/* 
 * Procedure partie(tapis: Tapis in/out, affTapis: tableau de [NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE] Caracteres in, joueur: tableau de [MAX_JOUEURS] Joueur in/out, nbJoueur: Entier in)
 * 
 * Deroulement de la partie
 * 
 * Necessite:
 * L'initialisation du tapis
 * L'initialisation de l'affichage du tapis
 * L'initialisation des joueurs
 * L'initialisation du nombre de joueur
 * 
 * Assure:
 * Le tapis est vide
 */

void jouerMemory();
/*
 * Procedure jouerMemory()
 * 
 * Jouer au jeu du memory
 */



// Debut dela classe Position
void init_Position( int ligne,  int colonne, Position* this)
{
	assert(this != NULL);
    this->ligne = ligne;
    this->colonne = colonne;
}

void affichage_Position( Position position)
{
	printf("ligne : %d - colonne : %d\n", position.ligne, position.colonne);
}

bool isEgalesPositions( Position a,  Position b)
{
    return ((a.ligne == b.ligne) && (a.colonne == b.colonne));
}

void setPosition( Position b, Position* this)
{
    this->ligne = b.ligne;
    this->colonne = b.colonne;
}
// Fin de la classe position

//Debut de la classe Carte
void init_Carte( Enseigne enseigne,  Valeur valeur, Carte* this)
{
    this->enseigne = enseigne;
    this->valeur = valeur;
};

bool couleurCarte( Carte c) //si true --> rouge
{
    return (((c.enseigne+1)/2)%2 == 1);
}

bool isEgalesCartes( Carte c1,  Carte c2)
{
    return ((c1.enseigne == c2.enseigne) && (c1.valeur == c2.valeur));
}

bool isPaireCarte( Carte c1,  Carte c2)
{
    return (couleurCarte(c1) == couleurCarte(c2)) && (c1.valeur == c2.valeur);
}
// Fin de la classe Carte

//Debut de la classe Jeu52
void init_Jeu52(Jeu52 jeu)
{
    int iEnseigne, iValeur;
    for(iEnseigne = 0; iEnseigne < NB_ENSEIGNES; iEnseigne++)
        for(iValeur = 0; iValeur < NB_VALEURS; iValeur++)
        {
            Carte iCarte = {iEnseigne, iValeur};
            *(jeu+iEnseigne*NB_VALEURS+iValeur) = iCarte;
        }
}

void permuter(Jeu52 jeu)
{
    int iCarte1 = rand()%NB_CARTES;
    int iCarte2 = rand()%NB_CARTES;
    Carte temp = *(jeu+iCarte1);
    *(jeu+iCarte1) = *(jeu+iCarte2);
    *(jeu+iCarte2) = temp;
}

void battre(Jeu52 jeu)
{
    do
    {
        permuter(jeu);
	} while (!bienBattu(jeu));
}

void calculPosCartes( Jeu52 jeu, int posCarte[NB_CARTES])
{
    for(int iCarte = 0; iCarte < NB_CARTES; iCarte++)
    {
        int iEnseigne = (*(jeu+iCarte)).enseigne;
        int iValeur = (*(jeu+iCarte)).valeur;
        posCarte[iEnseigne*NB_VALEURS+iValeur] = iCarte;
    }

}

void affichage( Jeu52 jeu)
{
    int posCarte[NB_CARTES];
    calculPosCartes(jeu, posCarte);
    for(int iCarte = 0; iCarte < NB_CARTES; iCarte++)
        printf("%d ", posCarte[iCarte]);
    printf("\n");
}

bool bienBattu( Jeu52 jeu)
{
    int posCarte[NB_CARTES], iCarte;
    calculPosCartes(jeu, posCarte);
    for(iCarte = 0; iCarte < NB_CARTES-1; iCarte++)
        if ((posCarte[iCarte]+1 == posCarte[iCarte+1]) || posCarte[iCarte] < 0 || posCarte[iCarte] >= NB_CARTES)
            return false;
    return (posCarte[NB_CARTES-1] < NB_CARTES && posCarte[NB_CARTES-1] >= 0);
}

// Fin de la classe Jeu52

//Debut de la classe CarteReele
void init_CarteReele( Carte carte,  EtatCarte etat, CarteReele* this)
{
    init_Carte(carte.enseigne, carte.valeur, &this->carte);
    this->etat = etat;
}
//Fin de la classe CarteReele

//Debut de la classe Tapis
void init_Tapis(Tapis tapis)
{
    int iEnseigne, iValeur;
    Jeu52 jeu;
    init_Jeu52(jeu);
    battre(jeu);
    for(iEnseigne = 0; iEnseigne < NB_ENSEIGNES; iEnseigne++)
        for(iValeur = 0; iValeur < NB_VALEURS; iValeur++)
            init_CarteReele(jeu[NB_VALEURS*iEnseigne+iValeur], CACHEE, &tapis[iEnseigne][iValeur]);
}
//Fin de la classe Tapis

//Debut de la classe Joueur
void init_Joueur( char nom[MAX_NOM],  bool humain,  Difficulte difficulte,  Position memoire[NB_CARTES],  int score, Joueur *joueur)
{
    int iChar, iPosition;
    for (iChar = 0; iChar < MAX_NOM; iChar++)
        joueur->nom[iChar] = nom[iChar];
    joueur->humain = humain;
    joueur->difficulte = difficulte;
    for (iPosition = 0; iPosition < NB_CARTES; iPosition++)
        joueur->memoire[iPosition] = memoire[iPosition];
    joueur->score = score;
}
//Fin de la classe Joueur

void trueStrCpy(char str1[],  char str2[],  int taille)
{
    for(int iChar = 0; iChar < taille && str2[iChar] != '\0'; iChar++)
        str1[iChar] = str2[iChar];
}

void clear_stdin()
{
	//Le probleme des solutions avec getchar ou scanf est que si la stdin est vide, ils attendent un retour a la ligne plutot que de terminer
    if (stdin) {
        int  descriptor = fileno(stdin);
        int       dummy;
        long      flags;
        
        flags = fcntl(descriptor, F_GETFL);
        fcntl(descriptor, F_SETFL, flags | O_NONBLOCK);
        
        do {
            dummy = getc(stdin);
        } while (dummy != EOF);
        
        fcntl(descriptor, F_SETFL, flags);
    }
    
    //int c;
    //while ((c = getchar()) != '\n'  && c != EOF);   //Linux mais ne marche pas si le flux est deja vide
    //scanf("%*[^\n]");
    
    //rewind(stdin);    //OS X
}


void clear()
{
	system("clear"); //Linux
//	system("cls");  //Windows
}

bool ppause()
{
    clear_stdin();
	return tolower(getchar()) == 'a';
//	system("pause"); //windows
}

CarteReele* tapisPosition(Tapis tapis,  Position position)
{
    return &tapis[position.ligne][position.colonne];
}

bool isDansTapis( Position position)
{
	int ligne = position.ligne;
	int colonne = position.colonne;
	return (ligne >= 0 && ligne < NB_LIGNES) && (colonne >= 0 && colonne < NB_COLONNES);
}

bool isDansMemoire( Position memoire[NB_CARTES],  Position position)
{
	for(int iMemoire = 0; iMemoire < NB_CARTES; iMemoire++)
		if(isEgalesPositions(memoire[iMemoire], position))
			return true;
	return false;
}

void stockageMemoireJoueur( Tapis tapis, Position memoire[NB_CARTES],  Position carte,  Difficulte difficulte)
{
    int iMemoire = 0;
    //si on l'a deja vu, on ne stocke rien
    
    while (iMemoire < NB_CARTES && !isEgalesPositions(memoire[iMemoire], memoireVide) && tapisPosition(tapis, memoire[iMemoire])->etat != RETIREE)
    {
        if (isEgalesCartes(tapisPosition(tapis, memoire[iMemoire])->carte, tapisPosition(tapis, carte)->carte))
            return;
        iMemoire++;
    }

    switch (difficulte)
    {
        case NAIF:
            break;
        case EXPERT:
        {
            if (iMemoire < NB_CARTES)
                setPosition(carte, &memoire[iMemoire]);
            break;
        }
        case ETOURDI:
        {
            if (iMemoire < NB_CARTES_ETOURDI)
                setPosition(carte, &memoire[iMemoire]);
            else if (iMemoire < NB_CARTES)
            {
                iMemoire = rand()%NB_CARTES_ETOURDI; //on remplace une carte au hasard dans la memoire
                setPosition(carte, &memoire[iMemoire]);
            }
            break;
        }
    }
}

void affichage_memoire( Position memoire[NB_CARTES])
{
	for(int iCase = 0; iCase < NB_CARTES; iCase++)
		affichage_Position(memoire[iCase]);
}

void memoriseCarte( Tapis tapis, Joueur* joueur,  Position carteRetournee[NB_ETAPES])  //a completer
{
    if (!joueur->humain)
        switch (joueur->difficulte)
        {
            case NAIF:
                break;
            case EXPERT: case ETOURDI:
            {
                for(int iCarte = 0; iCarte < NB_ETAPES; iCarte++)
					if (tapisPosition(tapis, carteRetournee[iCarte])->etat != RETIREE && !isDansMemoire(joueur->memoire, carteRetournee[iCarte]))
						stockageMemoireJoueur(tapis, joueur->memoire, carteRetournee[iCarte], joueur->difficulte);
                break;
            }
        }
}

void affichageTapis( char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE])
{
    for(int iLigne = 0; iLigne < NB_LIGNES_AFFICHAGE; iLigne++)
    {
        for (int iColonne = 0; iColonne < NB_COLONNES_AFFICHAGE; iColonne++)
            printf("%c", affTapis[iLigne][iColonne]);
        printf("\n");
    }
}

void init_affTapis(char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE])
{
    //On met toutes les cartes faces retournees
    for(int iLigne = 0; iLigne < NB_LIGNES_AFFICHAGE; iLigne++)
    {
        if(iLigne%TAILLE_LIGNE == 1)
        {
            for(int iColonne = 0; iColonne < NB_COLONNES_AFFICHAGE; iColonne++)
            {
                if (iColonne == 0 || iColonne == NB_COLONNES_AFFICHAGE-1)
                    affTapis[iLigne][iColonne] = ' ';
                else
                    affTapis[iLigne][iColonne] = (iColonne%TAILLE_COLONNE==1) ? '+' : '-';
            }
        }
        else if (iLigne == 0 || iLigne == NB_LIGNES_AFFICHAGE-1)
            for(int iColonne = 0; iColonne < NB_COLONNES_AFFICHAGE; iColonne++)
                affTapis[iLigne][iColonne] = ' ';
        else
        {
            for(int iColonne = 0; iColonne < NB_COLONNES_AFFICHAGE; iColonne+=3)
            {
                if ((iColonne/3)%2 == 0)
                    strcpy((*(affTapis+iLigne)+iColonne), " | ");
                else
                    strcpy((*(affTapis+iLigne)+iColonne), "~~~");
            }
            affTapis[iLigne][NB_COLONNES_AFFICHAGE-DECALAGE-1] = '|';
        }
    }

    //On pose maintenant les numeros des lignes ...
    for(int iLigne = TAILLE_LIGNE; iLigne < NB_LIGNES_AFFICHAGE; iLigne+=TAILLE_LIGNE)
    {
        affTapis[iLigne][0] = '0'+iLigne/TAILLE_LIGNE;
        affTapis[iLigne][NB_COLONNES_AFFICHAGE-1] = '0'+iLigne/TAILLE_LIGNE;
    }
    //... puis des colonnes
    for(int iColonne = 4; iColonne < NB_COLONNES_AFFICHAGE; iColonne+=TAILLE_COLONNE)
    {
        affTapis[0][iColonne] = 'A'+iColonne/TAILLE_COLONNE;
        affTapis[NB_LIGNES_AFFICHAGE-1][iColonne] = 'A'+iColonne/TAILLE_COLONNE;
    }
}

void lire_nbJoueurs(int* nbJoueurs)
{
    clear_stdin();
    switch (*nbJoueurs)
    {
        case -1:
        {
            printf("A combien voulez vous jouer ? (entre %d et %d)\n", MIN_JOUEURS, MAX_JOUEURS);
            scanf("%d", nbJoueurs);
            break;
        }
        case 0:
        {
            printf("Il est impossible de jouer sans joueur\n");
            *nbJoueurs = -1;
            break;
        }
        case 1:
        {
            printf("Il est impossible de jouer seul\n");
            *nbJoueurs = -1;
            break;
        }
        default:
        {
            printf("Entrez un nombre de joueurs valide !\n");
            *nbJoueurs = -1;
        }
    }
}

int lire_nom(char nom[MAX_NOM])
{
    clear_stdin();
    int iLettre = 0;
    printf("Entrez le nom du joueur (taille maximale : %d)\n", MAX_NOM-1);
    do
    {
        scanf("%c", &nom[iLettre]);
        iLettre++;
    } while (iLettre < MAX_NOM && nom[iLettre-1] != '\n'); //on autorise les ' '
    
    if (nom[iLettre-1]!='\n')
		return -1;
    return iLettre;
}

void lire_humain(bool* humain)
{
    char isHumain = 0;
    printf("Le joueur sera-t-il humain ? (o/n)\n");
    do
    {
        if (isHumain != 0)
        {
            clear_stdin();
            printf("Veuillez entrer 'o' ou 'n'\n");
        }
        scanf("%c", &isHumain);
    } while (!(isHumain == 'o' || isHumain == 'n'));
    
    *humain = (isHumain == 'o');
}

void lire_difficulte(Difficulte* difficulte,  bool humain)
{
    *difficulte = NAIF;
    if (!humain)
    {
        int niveau = -1;
        do
        {
            if (niveau != -1)
                printf("Merci de reessayer, ia selectionnee non valide\n");
            printf("Entrer la difficulte de l'IA desiree (NAIF=0, EXPERT=1, ETOURDI=2)\n");
            scanf("%d", &niveau);
        } while (niveau < 0 || niveau >= NB_IA);
        *difficulte = niveau;
    }
}

bool isNomPris(char nom[MAX_NOM], Joueur joueur[MAX_JOUEURS], int iJoueur)
{
	for(int curJoueur = 0; curJoueur < iJoueur; curJoueur++)
		if(strcmp(nom, joueur[curJoueur].nom) == 0)
			return true;
	return false;
}

void init_tab_joueur(Joueur joueur[MAX_JOUEURS], int* nbJoueurs)
{
    *nbJoueurs = -1;
    do
    {
        lire_nbJoueurs(nbJoueurs);
    } while (*nbJoueurs < MIN_JOUEURS || *nbJoueurs > MAX_JOUEURS);

    for(int iJoueur = 0; iJoueur < *nbJoueurs; iJoueur++)
    {
        printf("\n### Configuration du joueur %d ###\n", iJoueur+1);

        //on prend son nom
        char nom[MAX_NOM];
        int iLettre;
        do
        {
            iLettre = lire_nom(nom);
            if(iLettre != -1)
				nom[iLettre-1] = '\0';
			else
				printf("Le nom choisi fait plus de 10 caracteres\n");
			if(isNomPris(nom, joueur, iJoueur))
				printf("Le nom de joueur \"%s\" est deja utilise\n", nom);
        } while (iLettre == -1 || isNomPris(nom, joueur, iJoueur));   //on ne veut pas garder des noms trop long
        
        //on choisit si le joueur est humain
        bool humain;
        lire_humain(&humain);

        //si le joueur est un ordinateur, on entre sa difficulte
        Difficulte difficulte;
        lire_difficulte(&difficulte, humain);

        //on fixe sa memoire a vide
        Position memoire[NB_CARTES];
        int iCase;
        for (iCase = 0; iCase < NB_CARTES; iCase++)
            setPosition(memoireVide, &memoire[iCase]);

        //score initialement nul
        int score = 0;
        
        //on peut desormais initialiser le joueur
        init_Joueur(nom, humain, difficulte, memoire, score, &joueur[iJoueur]);
    }
    printf("\n");
}

void initialisation(Tapis tapis, char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], Joueur joueur[MAX_JOUEURS], int* nbJoueurs)
{
	init_Tapis(tapis);
	init_affTapis(affTapis);
	init_tab_joueur(joueur, nbJoueurs);
}

void afficheJoueur( Joueur joueur,  int iClassementJoueur)
{
    if (joueur.score != ABANDON)
        printf("|%10s|    %02d    |    %2d    |\n", joueur.nom, joueur.score, iClassementJoueur);
    else
        printf("|%10s|  ABANDON |    %2d    |\n", joueur.nom, iClassementJoueur);
}

int compareScore(const void* a, const void* b)
//si le joueur b a un score plus grand, il est classé avant le joueur a
{
    return ( (*(Joueur*)b).score - (*(Joueur*)a).score );
}

void affichageVainqueurs(Joueur joueur[MAX_JOUEURS], int nbJoueurs)
{
    qsort(joueur, nbJoueurs, sizeof(Joueur), compareScore);
    printf("    Nom       Score    Classement\n");
    int iClassement = 1;
    for (int iJoueur =0; iJoueur < nbJoueurs; iJoueur++)
    {
        if(iJoueur != 0 && joueur[iJoueur].score != joueur[iJoueur-1].score)
            iClassement = iJoueur + 1;
        afficheJoueur(joueur[iJoueur], iClassement);
    }
        
}

void placeCarte(char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], char affCarte[HAUTEUR_CARTE][LARGEUR_CARTE], Position position)
{
    position.ligne = position.ligne*TAILLE_LIGNE + 2;
    position.colonne = position.colonne*TAILLE_COLONNE + 3;
    for (int iLigne = 0; iLigne < HAUTEUR_CARTE; iLigne++)
        for (int iColonne = 0; iColonne < LARGEUR_CARTE; iColonne++)
            affTapis[position.ligne+iLigne][position.colonne+iColonne] = affCarte[iLigne][iColonne];
}

void changementCarte(Tapis tapis, char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], Position position, EtatCarte etat)
{
    char affCarte[HAUTEUR_CARTE][LARGEUR_CARTE];  //Correspond à un emplacement de carte dans le tableau d'affichage
    CarteReele* carte = tapisPosition(tapis, position);
    if (etat == VISIBLE)
    {
            trueStrCpy(affCarte[0], txtValeur[carte->carte.valeur], LARGEUR_CARTE);
            trueStrCpy(affCarte[1], txtEnseigne[carte->carte.enseigne], LARGEUR_CARTE);
	}
	else
		for (int iLigne = 0; iLigne < HAUTEUR_CARTE; iLigne++)
			trueStrCpy(affCarte[iLigne], affEtatCarte[etat][iLigne], LARGEUR_CARTE);
           
    tapis[position.ligne][position.colonne].etat = etat;
    placeCarte(affTapis, affCarte, position);
}

void lecturePosition(Position* position)
{
	char lettreColonne;
	int testScan = 0;
	int testLigneColonne = 0;
	do
	{
        clear_stdin();
		switch (testLigneColonne){
			case 1:
				printf("La colonne est correcte mais la ligne est incorrecte\n");
				break;

            case 2:
				printf("La ligne est correcte mais la colonne est incorrecte\n");
				break;

            case 0:
                break;

			default:
				printf("Merci de renseigner une position valide\n");
		}

        lettreColonne = 'z';
        position->ligne = 0;
        testLigneColonne = 0;

		printf("Entrez la position (ex: 1A)\n");
		testScan = scanf("%d%c", &(position->ligne), &lettreColonne); //on a recupere deux parametres
        printf("Position lue : %d%c\n", position->ligne, lettreColonne);
		position->colonne = (int)(toupper(lettreColonne))-'A';
        position->ligne -= 1;
/*		printf("Position colonne : %d\n", position->colonne);
        printf("Position ligne : %d\n", position->ligne);
        printf("Test scan : %d\n", testScan);*/
        if(!(isDansTapis(*position)))
        {
			if (!((position->ligne >= 0) && (position->ligne < NB_LIGNES))) //si la ligne n'est pas ok
				testLigneColonne += 1;
            if (!((position->colonne >= 0) && (position->colonne < NB_COLONNES))) //si la colonne n'est pas ok
				testLigneColonne += 2;
		}

	} while ((testScan != 2) || (testLigneColonne != 0));   //scanf() renvoie le nombre de parametres lus
}


void cacheMemoire(Tapis tapis, Position memoire[NB_CARTES])
{
    int iMemoire = 0;
    while ((iMemoire < NB_CARTES) && (!(isEgalesPositions(memoire[iMemoire], memoireVide))))
    {
        Position position = memoire[iMemoire];
        if (tapis[position.ligne][position.colonne].etat != RETIREE)
            tapis[position.ligne][position.colonne].etat = CACHEE;
        iMemoire++;
    }
}

void ia_memoire(Tapis tapis, int nbCartesRestantes, Position memoire[NB_CARTES], Position cartePrec, Position* position)
{
    //~ _dejaVuCarte: Tableau de [NB_COULEURS][NB_VALEURS] Booleen initialises a 0
    bool dejaVuCarte[NB_COULEURS][NB_VALEURS];
    for (int iCouleur = 0; iCouleur < NB_COULEURS; iCouleur++)
		for (int iValeur = 0; iValeur < NB_VALEURS; iValeur++)
			dejaVuCarte[iCouleur][iValeur] = false;
    
    
    int nbCartesCachees = 0;
    //~ _Si il y a une carte precedente:
    if (!isEgalesPositions(cartePrec, memoireVide) && isDansTapis(cartePrec))
    {
        CarteReele* carte = tapisPosition(tapis, cartePrec);
        carte->etat = VISIBLE;
        dejaVuCarte[couleurCarte(carte->carte)][carte->carte.valeur] = true;
        nbCartesCachees++;
    }
    //~ _dejaVuCarte[position carte precedente]
    //~ _Tant qu'on n'a pas parcouru toutes les cartes en memoire et que la carte est toujours sur le tapis:
    int iMemoire = 0;
    while ((iMemoire < NB_CARTES) && !(isEgalesPositions(memoire[iMemoire], memoireVide)))
    {
        CarteReele* carte = tapisPosition(tapis, memoire[iMemoire]);
        if (carte->etat == CACHEE)
        {
			nbCartesCachees++;
            carte->etat = VISIBLE;
            if (dejaVuCarte[couleurCarte(carte->carte)][carte->carte.valeur])	//~ _Si On a deja vu la paire de la carte courante:
            {
                *position = memoire[iMemoire];				//~ _Renvoie la position de la carte courante
                cacheMemoire(tapis, memoire);
                return;
            }
            else
                dejaVuCarte[couleurCarte(carte->carte)][carte->carte.valeur] = true;	//~ _dejaVuCarte[position carte courante] <- 1
        }
        iMemoire++;
    }
	
	//On choisit aleatoirement une carte parmi celles restantes et non memorisees
	int nbCartesCacheesHorsMemoire = nbCartesRestantes - nbCartesCachees;
	int iATirer = rand()%nbCartesCacheesHorsMemoire;
	
	//Puis on la tire
	for(int iCarte = 0; iCarte < NB_CARTES && iATirer >= 0; iCarte++)
	{
		int iLigne = iCarte/NB_COLONNES;
		int iColonne = iCarte%NB_COLONNES;
		CarteReele carte = tapis[iLigne][iColonne];
		if (carte.etat == CACHEE)
		{
			if (iATirer == 0)
				init_Position(iLigne, iColonne, position);
			iATirer--;
		}
	}
    cacheMemoire(tapis, memoire);
}

void carteAleatoireCachee(Tapis tapis, int iCarte, Position* position)
{
    int nbCache = 0;
    for(int iLigne=0; iLigne<NB_LIGNES; iLigne++)
        for(int iColonne=0; iColonne<NB_COLONNES; iColonne++)
        {
            CarteReele carte = tapis[iLigne][iColonne];
            if (carte.etat == CACHEE)
            {
                nbCache++;
                if(nbCache == iCarte)
                {
                    position->ligne = iLigne;
                    position->colonne = iColonne;
                }
            }
        }
}

void ia_naif(Tapis tapis,  int nbCartesRestantes, Position* position)
{
    int iCarte = rand()%nbCartesRestantes + 1;
    carteAleatoireCachee(tapis, iCarte, position);
}

void saisieCarte(Tapis tapis, Joueur joueur, int nbCartesRestantes, Position carteRetournee[NB_ETAPES], int iEtape)
{
    int test = 0;
    Position cartePrec = memoireVide;
    if (joueur.humain)
    {
        do
        {
            if(test == 1)
            {
				clear_stdin();
                printf("La carte n'est plus dans le tapis ou est deja retournee\n");
			}
            lecturePosition(&carteRetournee[iEtape]);
            test = 1;
        } while(tapisPosition(tapis, carteRetournee[iEtape])->etat != CACHEE);
    }
    else
    {
        switch (joueur.difficulte) {
            case NAIF:
            {
                ia_naif(tapis, nbCartesRestantes, &carteRetournee[iEtape]);
                break;
            }
            case EXPERT: case ETOURDI:
            {
                if(iEtape==1)
                    cartePrec = carteRetournee[0];
                ia_memoire(tapis, nbCartesRestantes, joueur.memoire, cartePrec, carteRetournee+iEtape);
                break;
			}
        }
    }
}

void choixDesCartes(Tapis tapis, Position carteRetournee[NB_ETAPES], char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], Joueur joueur,  int nbCartesRestantes)
{
    carteRetournee[0] = memoireVide;
    for(int iEtape=0; iEtape<NB_ETAPES; iEtape++)
	{
        if(joueur.humain)
        {
			printf("### Joueur : %s %s ###\n", txtTypes[0], joueur.nom);
            affichageTapis(affTapis);
		}
		saisieCarte(tapis, joueur, nbCartesRestantes, carteRetournee, iEtape);
		changementCarte(tapis, affTapis, carteRetournee[iEtape], VISIBLE);
		clear();
	}
}

void tourJoueur(Tapis tapis, char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], Joueur joueur[MAX_JOUEURS],  int nbJoueurs, int *iJoueur, int* nbCartesRestantes)
{
    printf("### C'est le tour de %s %s ### \n", txtTypes[(joueur[*iJoueur].humain)?0:joueur[*iJoueur].difficulte+1], joueur[*iJoueur].nom);

    printf("Appuyez sur A si vous souhaitez abandonner, ou sur une autre touche pour continuer\n");
    if (ppause())
        joueur[*iJoueur].score = ABANDON;     //L'abandon fait que l'on n'apparait en bas du tableau des scores, hors classement
    
    clear();
    
    Position carteRetournee[NB_ETAPES];
	choixDesCartes(tapis, carteRetournee, affTapis, joueur[*iJoueur], *nbCartesRestantes);
    
    printf("### %s %s a choisi: ### \n", txtTypes[(joueur[*iJoueur].humain)?0:joueur[*iJoueur].difficulte+1], joueur[*iJoueur].nom);  
	affichageTapis(affTapis);
    
    printf("Appuyer sur entrée pour continuer\n");
	ppause();
        
	
	Carte carte1 = tapis[carteRetournee[0].ligne][carteRetournee[0].colonne].carte;
	Carte carte2 = tapis[carteRetournee[1].ligne][carteRetournee[1].colonne].carte;
	if (isPaireCarte(carte1, carte2))
	{
		for(int iEtape = 0; iEtape < NB_ETAPES; iEtape++)
			changementCarte(tapis, affTapis, carteRetournee[iEtape], RETIREE); //On retire les deux cartes
		*nbCartesRestantes -= 2;
		// Retirer carte memoire !!!!
        if (joueur[*iJoueur].score != ABANDON)
        {
            joueur[*iJoueur].score += 1;
            *iJoueur -= 1;  //On décrémente l'identificateur du joueur en cour de tel sorte que le joueur suivant a jouer soit lui même
        }
	}
	else
		for(int iEtape = 0; iEtape < NB_ETAPES; iEtape++)
			changementCarte(tapis, affTapis, carteRetournee[iEtape], CACHEE);
	
	for (int jJoueur = 0; jJoueur < nbJoueurs; jJoueur++)   //Tous les joueurs memorisent la carte chacun à leur tour
		memoriseCarte(tapis, &joueur[jJoueur], carteRetournee);

	clear();
}

bool testTapis( int nbCartesRestantes) //Test si le tapis est vide
{
    return (!(nbCartesRestantes == 0));
}

void partie(Tapis tapis, char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE], Joueur joueur[MAX_JOUEURS],  int nbJoueurs)
{
    clear();
    int iJoueur = rand()%nbJoueurs;
    int nbCartesRestantes = NB_CARTES;
    int nbAbandons = 0;
    while (testTapis(nbCartesRestantes) && nbAbandons != nbJoueurs)
    {
        if (joueur[iJoueur].score != ABANDON)
            tourJoueur(tapis, affTapis, joueur, nbJoueurs, &iJoueur, &nbCartesRestantes);
        else
            nbAbandons++;
        
        iJoueur++;
        if(nbAbandons == nbJoueurs)
            return;
        if(iJoueur == nbJoueurs)
        {
            nbAbandons = 0;
            iJoueur = 0;
        }
    }
}

void affichage_tableau_debug( Tapis tapis)
{
    char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE];
    init_affTapis(affTapis);
    for(int iLigne = 0; iLigne < NB_LIGNES; iLigne++)
        for(int iColonne = 0; iColonne < NB_COLONNES; iColonne++)
        {
            Position position;
            init_Position(iLigne, iColonne, &position);
            CarteReele* carte = &tapis[iLigne][iColonne];
            EtatCarte etat = carte-> etat;
            changementCarte(tapis, affTapis, position, VISIBLE);
            carte->etat = etat; //changementCarte modifie egalement l'etat, donc on le sauvegarde
        }
       
	for(int iLigne = 0; iLigne < NB_LIGNES_AFFICHAGE; iLigne++)
	{
		for(int iColonne = 0; iColonne < NB_COLONNES_AFFICHAGE; iColonne++)
			printf("%c", affTapis[iLigne][iColonne]);
		printf("\n");
	}
}

void jouerMemory()
{
	//_Mise en place du jeu
	Tapis tapis;
	char affTapis[NB_LIGNES_AFFICHAGE][NB_COLONNES_AFFICHAGE];
	Joueur joueur[MAX_JOUEURS];
	int nbJoueurs;
    
    clear();
	initialisation(tapis, affTapis, joueur, &nbJoueurs);
	affichage_tableau_debug(tapis);
	partie(tapis, affTapis, joueur, nbJoueurs);
	affichageVainqueurs(joueur, nbJoueurs);
}

int main()
{
	srand(time(NULL));
    jouerMemory();

    return EXIT_SUCCESS;
}
