
import afficheur.AfficheurGraphics;
import java.awt.Component;
import java.util.ArrayList;
import javax.swing.AbstractButton;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.JTextField;

/** J ai fait un rm *.java au lieu d un rm *.class donc plus de source, j ai decompile mon .class :
 * je dois refaire tous mes commentaires.
 * @author Guillaume
 *
 */
public class Fenetre
extends JPanel {
    public static void main(String[] arrstring) {
        JFrame jFrame = new JFrame("Interface graphique");
        jFrame.setDefaultCloseOperation(3);
        Fenetre.definitionContenu(jFrame);
    }

    static void definitionContenu(JFrame jFrame) {
        JMenuBar jMenuBar = new JMenuBar();
        Fenetre.definitionMenus(jMenuBar);
        jFrame.setJMenuBar(jMenuBar);
        jFrame.setSize(350, 250);
        jFrame.setVisible(true);
        // Afficheur perso elabore a partir de java.awt.Graphics;
        AfficheurGraphics afficheurGraphics = new AfficheurGraphics();
       // AfficheurSVG afficheurSVG = new AfficheurSVG("Carte","Une carte du reseau", 200,150);
        //JButton jButton = new JButton("bouton 1");
       // JButton jButton2 = new JButton("bouton 2");
        jFrame.add((Component)afficheurGraphics, "Center");
       // jFrame.add((Component)jButton, "West");
       // jFrame.add((Component)jButton2, "East");
    }

    static void definitionMenus(JMenuBar jMenuBar) {
        CstrMenu cstrMenu = new CstrMenu("Paquet", jMenuBar);
        cstrMenu.setMnemonic(80);
        CstrMenu cstrMenu2 = new CstrMenu("Noeud", jMenuBar);
        cstrMenu2.setMnemonic(78);
        Fenetre.definitonSousMenus((JMenu)cstrMenu, (JMenu)cstrMenu2);
    }

    static void definitonSousMenus(JMenu jMenu, JMenu jMenu2) {
        CstrMenu cstrMenu = new CstrMenu("Emetteur", jMenu);
        cstrMenu.setMnemonic(69);
        CstrMenu cstrMenu2 = new CstrMenu("Recepteur", jMenu);
        cstrMenu2.setMnemonic(82);
        CstrMenu cstrMenu3 = new CstrMenu("Contenu", jMenu);
        cstrMenu3.setMnemonic(67);
        JTextField jTextField = new JTextField("Entrez votre contenu");
        JLabel jLabel = new JLabel("Un JTextField");
        cstrMenu3.add(jTextField);
        CstrMenu cstrMenu4 = new CstrMenu("Activer", jMenu2);
        cstrMenu4.setMnemonic(65);
        CstrMenu cstrMenu5 = new CstrMenu("Desactiver", jMenu2);
        cstrMenu5.setMnemonic(68);
        CstrMenu cstrMenu6 = new CstrMenu("Ajouter", jMenu2);
        cstrMenu6.setMnemonic(65);
        JTextField jTextField2 = new JTextField("Entrez votre contenu");
        JLabel jLabel2 = new JLabel("Un JTextField");
        cstrMenu6.add(jTextField2);
        CstrMenu cstrMenu7 = new CstrMenu("Supprimer", jMenu2);
        cstrMenu4.setMnemonic(83);
        CstrMenu cstrMenu8 = new CstrMenu("Mobilite", jMenu2);
        cstrMenu8.setMnemonic(77);
        Fenetre.radioGroup((JMenu)cstrMenu, (JMenu)cstrMenu2, (JMenu)cstrMenu4, (JMenu)cstrMenu5, (JMenu)cstrMenu7, (JMenu)cstrMenu8);
    }

    static void radioGroup(JMenu jMenu, JMenu jMenu2, JMenu jMenu3, JMenu jMenu4, JMenu jMenu5, JMenu jMenu6) {
        ButtonGroup buttonGroup = new ButtonGroup();
        ButtonGroup buttonGroup2 = new ButtonGroup();
        ButtonGroup buttonGroup3 = new ButtonGroup();
        ButtonGroup buttonGroup4 = new ButtonGroup();
        ButtonGroup buttonGroup5 = new ButtonGroup();
        ButtonGroup buttonGroup6 = new ButtonGroup();
        ArrayList<JRadioButtonMenuItem> arrayList = new ArrayList<JRadioButtonMenuItem>();
        Fenetre.instancierNoeuds(arrayList, jMenu, 6, buttonGroup);
        ArrayList<JRadioButtonMenuItem> arrayList2 = new ArrayList<JRadioButtonMenuItem>();
        Fenetre.instancierNoeuds(arrayList2, jMenu2, 6, buttonGroup2);
        ArrayList<JRadioButtonMenuItem> arrayList3 = new ArrayList<JRadioButtonMenuItem>();
        Fenetre.instancierNoeuds(arrayList3, jMenu3, 6, buttonGroup3);
        ArrayList<JRadioButtonMenuItem> arrayList4 = new ArrayList<JRadioButtonMenuItem>();
        Fenetre.instancierNoeuds(arrayList4, jMenu4, 6, buttonGroup4);
        ArrayList<JRadioButtonMenuItem> arrayList5 = new ArrayList<JRadioButtonMenuItem>();
        Fenetre.instancierNoeuds(arrayList5, jMenu5, 6, buttonGroup5);
        ArrayList<JRadioButtonMenuItem> arrayList6 = new ArrayList<JRadioButtonMenuItem>();
        Fenetre.instancierNoeuds(arrayList6, jMenu6, 6, buttonGroup6);
    }

    static void instancierSubMenus(ArrayList<JMenu> arrayList, String[] arrstring, JMenu jMenu, int n) {
        for (int i = 0; i < n; ++i) {
            arrayList.add(new JMenu(arrstring[i]));
            jMenu.add(arrayList.get(i));
        }
    }

    static void instancierNoeuds(ArrayList<JRadioButtonMenuItem> arrayList, JMenu jMenu, int n, ButtonGroup buttonGroup) {
        for (int i = 0; i < n; ++i) {
            arrayList.add(new JRadioButtonMenuItem("Noeud " + String.valueOf(i), true));
            jMenu.add(arrayList.get(i));
            buttonGroup.add(arrayList.get(i));
        }
    }
}