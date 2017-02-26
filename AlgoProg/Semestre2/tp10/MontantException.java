/**
  * Cette exception indique que le montant d'une transaction est invalide
  * @author	Thibault Meunier
  * @version	1.0
  */

public class MontantException extends java.io.IOException {

	public MontantException() {
		super("MontantNull");
	}

	public MontantException(String message) {
		super(message);
	}

    public MontantException(double montant, String message) {
        this((montant < 0) ? "Credit negatif" : "Debit positif" + " : " + montant + " " + message);
    }

}
