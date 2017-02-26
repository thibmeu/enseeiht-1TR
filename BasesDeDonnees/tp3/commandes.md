# TP3 Base de Donnees
Contraintes, SQL et LMD

## Base "gestion\_cd": Modification du schema d'une table
### Table `emprunt` initiale
```bash
 num_cd | num_p 
--------+-------
      1 |     1
      2 |     2
      1 |     2
      1 |     4
```
### Ajout d'une nouvelle colonne
```sql
ALTER TABLE emprunt ADD COLUMN date Date;
```
```bash
 num_cd | num_p | date    
--------+-------+------
      1 |     1 |
      2 |     2 |
      1 |     2 |
      1 |     4 |
```
Par defaut, la nouvelle colonne contient uniquement des valeurs `NULL`



Pour pallier a ce probleme, on peut soit definir une date pour chacun des anciens emprunts, soit retirer la colonne et la rajouter avec une date par defaut (la courante)
```sql
ALTER TABLE emprunt DROP date;
ALTER TABLE emprunt ADD COLUMN date Date DEFAULT current_date NOT NULL;
```
```bash
 num_cd | num_p |    date    
--------+-------+------------
      1 |     1 | 2016-03-30
      2 |     2 | 2016-03-30
      1 |     2 | 2016-03-30
      1 |     4 | 2016-03-30
```

### Ajout d'une nouvelle colonne a la cle primaire
On supprime l'ancienne
```sql
ALTER TABLE emprunt DROP CONSTRAINT pk_emp;
```
Puis on ajoute la nouvelle avec la colonne en plus
```sql
ALTER TABLE emprunt ADD CONSTRAINT pk_emp PRIMARY KEY(num_cd, num_p, date);
```

## Base "gestion\_cd": Requetes SQL
### Affichage par ordre alphabetique des personnes ayant emprunte un cd
```sql
SELECT DISTINCT nom, num_p
FROM emprunt
JOIN personne ON num_per=num_p ORDER BY nom ASC;
```

### Personne ayant emprunte au moins un cd de la personne Dupont
```sql
SELECT DISTINCT nom, num_p
FROM emprunt
JOIN personne ON num_per=num_p
WHERE num_cd IN (SELECT num_cd FROM c_d JOIN personne ON prop=num_per WHERE nom='Dupont');
```

### Personne ayant emprunter le cd 1
```sql
SELECT DISTINCT nom, num_p
FROM emprunt
JOIN personne ON num_p=num_per
WHERE num_cd=1
ORDER BY nom ASC;
```

### Personne ayant emprunte au moins un cd enprunte par Durand
```sql
SELECT DISTINCT nom, num_p
FROM emprunt
JOIN personne ON num_per=num_p
WHERE nom!='Durand'
AND num_cd IN (SELECT DISTINCT num_cd FROM emprunt JOIN personne ON num_p=num_per WHERE nom='Durand');
```

### Personne ayant emprunte au moins deux cds differents
```sql
SELECT num_per, nom, count(*) AS nb_emprunts
FROM emprunt
JOIN personne ON num_per=num_p
GROUP BY num_per, nom;
```
