# TP1 Bases de Donnees
Utilisation de PostGre (PSQL)

## Connexion a la base de donnees
```bash
psql -h gailuron -U tmeunier -d tmeunier [-f commandes.sql]
```

## Commandes de l'interpreteur
```bash
\? affichage de la doc
\h affichage des differentes commandes
\d affichage des tables
\d TABLE affichage des caracteristiques de la table
```

## Creation des tables
### Allergie
```sql
CREATE TABLE allergie (
nom VARCHAR(30) PRIMARY KEY,
nature TEXT
);
```

### Date
```sql
CREATE TABLE date (
date DATE PRIMARY KEY
);
```

### Hopital
```sql
CREATE TABLE hopital (
nom VARCHAR(30) PRIMARY KEY,
adresse TEXT
);
```

### Medecin
On peut **referencer des tables non creees**
```sql
CREATE TABLE medecin (
num_medecin SERIAL PRIMARY KEY,
nom VARCHAR(30) NOT NULL,
prenom VARCHAR(30) NOT NULL,
salaire INT CHECK (salaire >= 2000),
nom_h VARCHAR(30) REFERENCES service (nom_hopital),
nom_s VARCHAR(30) REFERENCES service (nom_service)
);

```

### Service
```sql
CREATE TABLE service (
nom_service VARCHAR(30) PRIMARY KEY,
nom_hopital VARCHAR(30) NOT NULL UNIQUE REFERENCES hopital,
chef INTEGER REFERENCES medecin,
batiment VARCHAR(30) NOT NULL
);
```

### Patient
```sql
CREATE TABLE patient (
num_dossier INT PRIMARY KEY,
nom VARCHAR(30) NOT NULL,
prenom VARCHAR(30) NOT NULL,
ddn DATE,
num_medecin_traitant INT REFERENCES medecin
);
```

### Atteint
```sql
CREATE TABLE atteint (
date DATE REFERENCES patient,
num_patient INT REFERENCES patient,
maladie TEXT NOT NULL
);
```

### Sensible
```sql
CREATE TABLE sensible (
allergie VARCHAR(30) REFERENCES allergie,
num_patient INT REFERENCES patient,
degre INT
);
```

## Insertion dans les tables et tests
### Insertion
#### Insertion simple
```sql
INSERT INTO hopital VALUES ('Rangueil', 'Toulouse');
```
On observe ainsi
```bash
select * from hopital;
   nom    | adresse  
----------+----------
 Rangueil | Toulouse
```

#### Insertion avec reference
Quand la reference n'existe pas, on insere avec ```NULL```
```sql
INSERT INTO service VALUES ('Chirurgie', NULL, 'Hall C', 'Rangueil');
```
La table presente une valeur **non initialisee** (un trou)
```bash
select * from service;
 nom_service | chef | batiment | nom_hopital 
-------------+------+----------+-------------
 Chirurgie   |      | Hall C   | Rangueil
```

Dans un cas normal, il suffit de connaitre les differentes cles primaires
```sql
INSERT INTO medecin VALUES (1, 'Dupont', 'Gerard', 4200, 'Rangueil', 'Chirurgie');
```
