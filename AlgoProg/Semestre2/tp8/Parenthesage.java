

public class Parenthesage {

    public static boolean verif(String s){
        PileChainee<Character> pile = new PileChainee<Character>();
        for (final char curChar : s.toCharArray()){
            switch (curChar) {
                case '(': case '[': case '{':
                    pile.empiler(curChar);
                    break;
                case ')':
                    if (pile.estVide() || pile.sommet() != '(')
                        return false;
                    if (!pile.estVide())
                        pile.depiler();
                    break;
                case ']':
                    if (pile.estVide() || pile.sommet() != '[')
                        return false;
                    if (!pile.estVide())
                        pile.depiler();
                    break;
                case '}':
                    if (pile.estVide() || pile.sommet() != '{')
                        return false;
                    if (!pile.estVide())
                        pile.depiler();
                    break;
                default:
                    break;
            }
        }
        return pile.estVide();
    }

    public static void main(String[] args){
        assert args.length == 1;
        System.out.println("Parenthesage : " + verif(args[0]));
    }

}
