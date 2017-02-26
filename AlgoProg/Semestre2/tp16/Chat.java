import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.TreeSet;
import java.util.Observable;
import java.util.Observer;
import java.util.Iterator;

public class Chat extends Observable implements Iterable<Message> {

    private String nom;
	private List<Message> messages;
    private boolean changed = false;

	public Chat(String nom) {
        this.nom = nom;
		this.messages = new ArrayList<Message>();
	}
    
    public String getNom() {
        return nom;
    }

	public void ajouter(Message m) {
		this.messages.add(m);
        this.setChanged();
        this.notifyObservers(m);
	}

    public Iterator<Message> iterator() {
        return messages.iterator();
    }

}
