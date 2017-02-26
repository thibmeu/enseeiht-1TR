/**
  * Cette exception indique que le dépôt initial d'un compte est invalide.
  * @author	Xavier Crégut
  * @version	1.2
  */
public class DepotInitialException extends java.io.IOException {

	public DepotInitialException(String message) {
		super(message);
	}

}
