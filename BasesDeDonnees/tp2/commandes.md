# TP2 Bases de Donnees
Contraintes, SQL et LMD

## Prise de contact avec la base et l'environement PSQL : base "gestionx\_cd"
Apres avoir vider la base des differentes tables preexistantes, on lance le script `exo1.sql`.

### Description de la base
Avec `\d`, on visualise les tables sur lesquelles on travaille
```bash
 Schéma |         Nom          |   Type   | Propriétaire 
--------+----------------------+----------+--------------
 public | c_d                  | table    | tmeunier
 public | c_d_num_cd_seq       | séquence | tmeunier
 public | emprunt              | table    | tmeunier
 public | personne             | table    | tmeunier
 public | personne_num_per_seq | séquence | tmeunier
```

Avec `\d table`, on recupere les caracteristiques de la table

#### Table `personne`
```bash
 Colonne |         Type          |                       Modificateurs                        
---------+-----------------------+------------------------------------------------------------
 num_per | integer               | non NULL Par défaut, nextval('personne_num_per_seq'::text)
 nom     | character varying(40) | non NULL
 tel     | character varying(10) | 
Index :
    "pk_pers" PRIMARY KEY, btree (num_per)
```

#### Table `emprunt`
```bash
 Colonne |  Type   | Modificateurs 
---------+---------+---------------
 num_cd  | integer | non NULL
 num_p   | integer | non NULL
Index :
    "pk_emp" PRIMARY KEY, btree (num_cd, num_p)
Contraintes de clés étrangères :
    "fk_cd" FOREIGN KEY (num_cd) REFERENCES c_d(num_cd)
    "fk_pers" FOREIGN KEY (num_p) REFERENCES personne(num_per)
```

#### Table `c_d`
```bash
 Colonne |         Type          |                    Modificateurs                     
---------+-----------------------+------------------------------------------------------
 num_cd  | integer               | non NULL Par défaut, nextval('c_d_num_cd_seq'::text)
 auteur  | character varying(40) | non NULL
 titre   | character varying(60) | 
 prop    | integer               | non NULL
Index :
    "pk_cd" PRIMARY KEY, btree (num_cd)
```

### Tests des contraintes
#### Non multiplicite de cle primaire
On insere dans la classe personne avec une cle primaire preexistante.
```bash
 num_per |   nom   |    tel     
---------+---------+------------
       1 | Dupont  | 
       2 | Durand  | 0561616161
       3 | La Joie | 0561101010
       4 | Doudou  | 
       5 | Mimi    | 0562626262
       0 | Amiga   | 
       6 | Pipite  | 0160666666
```

En executant :
```sql
INSERT INTO personne VALUES (1, 'Meunier', '0612345678');
```
On recoit l'erreur `ERROR:  duplicate key violates unique constraint "pk_pers"`.

#### Referencement
On tente de supprimer un cd deja reference.
```sql
DELETE FROM c_d WHERE num_cd = 1;
```
On recoit alors l'erreur `ERROR:  update or delete on "c_d" violates foreign key constraint "fk_cd" on "emprunt"`.

## Requetes SQL et "base bdx\_commandes"
On execute le script `exo2.sql`.
### Description de la base
```bash
 Schéma |   Nom    | Type  | Propriétaire 
--------+----------+-------+--------------
 public | client   | table | tmeunier
 public | commande | table | tmeunier
 public | produit  | table | tmeunier
```

#### Table `client`
```bash
 num_cli |   nom    |  prenom  |       adresse        | telephone 
---------+----------+----------+----------------------+-----------
       1 | Dupont   | Robert   | Rue de l Aubepine    | 
       2 | Iznogoud |          | Place du Calife      | 
       3 | Martin   | Isabelle | Rue des Cerises      | 561616161
       4 | Martin   | Celine   | Rue des Tilleuls     | 534343434
       5 | Durand   | Alain    | Rue de la Colombette | 561626262
      10 | Croquant | J.       | Le bois qui tue      | 
       6 | Durand   | Alain    | Rue Camichel         | 561585858
```

#### Table `commande`
```bash
 num_c | num_p | quantite |    date    
-------+-------+----------+------------
     1 |     1 |        3 | 1999-10-30
     1 |     1 |        4 | 1999-11-30
     1 |     1 |        1 | 1999-09-10
     2 |     1 |       45 | 2000-01-10
```

#### Table `produit`
```bash
 num_pdt |   nom   |  prix  |   description    
---------+---------+--------+------------------
       1 | Souris  |  54.65 | Souris 3 boutons
       2 | Souris  |  45.50 | Souris 2 boutons
       3 | Souris  |   35.0 | Souris 1 bouton
       4 | Clavier |  125.0 | Azerty
       5 | Clavier |  130.0 | Qwerty
       6 | Ecran   | 1200.0 | Ecran 17p.
       7 | Ecran   |  800.0 | Ecran 15p.
```

### Mise a jour
On va mettre a jour la table `commande` en fonction des demandes de l'enonce
- Martin Isabelle a commande 65 souris (type 54.50 euros) le 12/09/2015
```sql
INSERT INTO commande VALUES (3, 1, 65, '2015-09-12');
```
- ...

### Requetes
--> sur 8 points a l'examen
- Liste des commandes avec le nom des clients, les objets commandes, et les dates classes par ordre chronologique des commandes.
```sql
SELECT c.nom AS nom_client, p.nom AS nom_produit, date
FROM commande
JOIN client AS c ON num_cli = num_c
JOIN produit AS p ON num_pdt = num_p
ORDER BY date ASC;
```

- Liste des objets commandes avec la quantite totale demandee et le nombre de commandes de ces objets : on se contente d'abord du numero de chaque objet puis on souhaite connaitre le nom des objets.
```sql
SELECT nom, sum(quantite), count(*)
FROM commande
JOIN produit ON num_pdt = num_p
GROUP BY num_p, nom;
```

- Nombre de commandes de chaque client ayant passe au moins une commande
```sql
SELECT nom, count(*)
FROM commande
JOIN client ON num_cli = num_c
GROUP BY num_c, nom;
```

- Liste des clients qui ont effectues plus de 2 commandes
```sql
SELECT nom, count(*) AS total
FROM commande
JOIN client ON num_cli = num_c
GROUP BY num_c, nom
HAVING count(*) >= 2;
```

### Manipulation d'une vue
**Vue** : Table virtuelle contenant le resultat d'une commande SQL.

#### Creation d'une vue
```sql
CREATE VIEW v_client AS
SELECT c.nom AS nom_client, sum(quantite*prix)
FROM commande
JOIN produit ON num_pdt = num_p
JOIN client AS c ON num_cli = num_c
GROUP BY num_c, c.nom;
```

#### Utilisation d'une vue
```sql
SELECT nom_client
FROM v_client
WHERE sum >= 1000;
```

#### Caractere dynamique d'une vue
On ajoute une commande dans la table `commande`
```sql
INSERT INTO commande VALUES (6, 2, 10, '2016-03-01');
```
En regardant a nouveau la vue, on constante qu'elle a ete modifiee:
```sql
SELECT * FROM v_client;
```

#### Destruction d'une vue
```sql
DROP VIEW v_client;
```
