

public class Triangle{
    
    public static void main(String args[]){
        //Sommets du triangle
        Point A = new Point(3, 2);
        Point B = new Point(11, 4);
        Point C = new Point(6, 9);

        //Aretes
        Segment AB = new Segment(A, B);
        Segment AC = new Segment(A, C);
        Segment BC = new Segment(B, C);

        //Barycentre
        Point D = new Point(0, 0);
        D.translater(1./3*A.getX(), 1./3*A.getY());
        D.translater(1./3*B.getX(), 1./3*B.getY());
        D.translater(1./3*C.getX(), 1./3*C.getY());
        D.afficher();
    }

}
