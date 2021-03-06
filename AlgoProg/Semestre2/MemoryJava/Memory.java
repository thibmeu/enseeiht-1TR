
public class Memory {
	
	public static void main (String[] argv) {
		/*java Memory largeurEcran nbFamilles tailleFamille -[mefiant|confiant] nom@{humain|naif|expert|tricheur}*/
		if ((argv.length < 4 && argv[3] != "mefiant" && argv[3] != "confiant") || argv.length < 5) {
			throw new RuntimeException("Il faut au moins un joueur pour jouer");
		}
		
		int largeurEcran = StringInteger.stringToPositiveInt(argv[0]);
		int nbFamilles = StringInteger.stringToPositiveInt(argv[1]);
		int tailleFamille = StringInteger.stringToPositiveInt(argv[2]);

		JeuCartesMemory<String, Integer> jeu = FabriqueJeuCartes.jeuFamilles(nbFamilles, tailleFamille);
		jeu.battre();
		
		AfficheurTapis afficheur = new AfficheurTapis(jeu, largeurEcran);
		
		Arbitre leChef = new Arbitre(afficheur);
		
		int iJoueur = 3;
		boolean mefiant = true;
		if (argv[3].equals("-confiant")) {
			mefiant = false;
			iJoueur++;
		}
		if (argv[3].equals("-mefiant")) {
			iJoueur++;
		}
		
		for (; iJoueur < argv.length; iJoueur++) {
			String[] joueurDescription = argv[iJoueur].split("@");
			if (joueurDescription.length != 2) {
				throw new RuntimeException("Le joueur " + iJoueur + "est mal formate : " + argv[iJoueur]);
			}
			
			leChef.inscrire(new JoueurReel(joueurDescription[0], joueurDescription[1]));
		}
		
		leChef.arbitrer(jeu, tailleFamille, mefiant);
	}
	
}
