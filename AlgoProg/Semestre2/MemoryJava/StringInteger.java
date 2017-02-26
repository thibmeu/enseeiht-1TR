
public class StringInteger {
	
	public static int stringToPositiveInt(String s) {
		int res = Integer.parseInt(s);
		if (res <= 0)
			throw new RuntimeException("Tout les entiers sont positifs !");
		return res;
	}
	
}
