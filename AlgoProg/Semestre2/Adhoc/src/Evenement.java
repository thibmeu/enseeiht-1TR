/**
 * @author Driouich Ilias
 * @version 1.0
 */

public class Evenement implements Comparable {
	
	
	private int date;
	private Operation operation;
	
	public void Evenement(int date, Operation operation){
		this.operation = operation;
		this.date = date;
	}
	
	public void seProduire(Simulateur simulateur) {
		operation.executer(simulateur, date);
	}
	
	public int compareTo(Evenement e){
		if (date < e.date) {
			return -1;
		}
		return date > e.date;
	}
	
		 
}
