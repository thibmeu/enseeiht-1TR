import java.io.*;

/** Quelques méthodes pour lire à partir du clavier.
 *  @author Xavier Crégut (très largement inspiré par Cay Horstmann) */
public class Console {
	/** Afficher un prompt à l'écran (sans passage à la ligne) */
	public static void printPrompt(String prompt) {
		System.out.print(prompt + " ");
		System.out.flush();	// forcer l'écriture en l'absence de '\n'
	}

   /** Lire une chaîne de caractères à partir du clavier.  La chaîne se 
	 * termine par un retour à la ligne (qui n'en fait pas partie) (cf corejava)
	 * @return la ligne lue à partir du clavier (sans le retour à la ligne) */
	public static String readLine() {
		int ch;
		String r = "";
		boolean done = false;
		while (!done) {
			try {
				ch = System.in.read();
				if (ch < 0 || (char) ch == '\n') {
					done = true;
				} else if ((char) ch != '\r') {
							// weird--it used to do \r\n translation
					r = r + (char) ch;
				}
			} catch (IOException e) {
				done = true;
			}
		}
		return r;
	}

    public int atoi(String s) throws IOException {
        if (s.isEmpty()) {
            throw new IOException("String is empty !");
        }

        int iChar = 0;
        boolean positive = true;
        if (s.charAt(iChar) == '-') {
            positive = false;
            iChar++;
        } else if (s.charAt(iChar) == '+') {
            iChar++;
        }
        
        int r = 0;

        for (; iChar < s.length(); iChar++) {
            char curChar = (char)((int) s.charAt(iChar) - (int) '0');
            if (curChar < 0 || curChar >= 10)
                throw new IOException("Not a valid integer");
            r = r*10 + (int) curChar;
        }

        if (!positive) {
            r = -r;
        }
        return r;
    }

    public static int readInt(String message) {
        int r = 0;

        boolean done;
        do {
            done = true;
            Console.printPrompt(message);
            String intString = readLine();
            
            try {
                r = new Console().atoi(intString);
            } catch (IOException e) {
                System.out.println("Everything could happen but there" + e);
            } finally {
                done = false;
            }
        } while (!done);

        return r;
    }
}
