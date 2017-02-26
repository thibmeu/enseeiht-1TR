

/**
 * 
 * @author Abdelmalek LAMINE
 *
 */

public class ProtocoleDSR implements Protocole {

	IdentifiantPaquet identifiant = new IdentifiantPaquet();
	
	@Override
	public void demandeRoute(String IP1, String IP2) {
		Paquet demandeRoute = new PaquetRoute(IP1, IP2, identifiant.getNouveauIdentifiant());
		envoyerPaquet(IP1, demandeRoute);
	}

	@Override
	public void reponseDemandeRoute(String IP1, String IP2) {
		// TODO Auto-generated method stub
	}

	@Override
	public boolean envoyerPaquet(String IPSource, Paquet lePaquet) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void envoyerPaquet(String IP1, Message leMessage, String IP2) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void recevoirPaquet(String IP, Paquet lePaquet) {
	
	}

}
