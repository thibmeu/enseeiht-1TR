CREATE TABLE client (
	num_cli   int4 not null,
	nom       varchar(40) not null,
	prenom    varchar(40),
	adresse   varchar(60) not null,
	telephone varchar(20),
	CONSTRAINT pk_client PRIMARY KEY(num_cli));

CREATE TABLE produit (
	num_pdt     int4 not null,
	nom         varchar(40),
	prix	    numeric not null,
	description varchar(60),
	CONSTRAINT pk_produit PRIMARY KEY(num_pdt));

CREATE TABLE commande (
	num_c INTEGER NOT NULL,
	num_p INTEGER NOT NULL,
	quantite INTEGER DEFAULT 1,
	date DATE,
	CONSTRAINT pk_com PRIMARY KEY(num_c, num_p, date),
	CONSTRAINT fk_client FOREIGN KEY(num_c) REFERENCES client(num_cli),
	CONSTRAINT fk_produit FOREIGN KEY(num_p) REFERENCES produit(num_pdt));

INSERT INTO client VALUES (1, 'Dupont', 'Robert', 'Rue de l Aubepine', NULL);
INSERT INTO client VALUES (2, 'Iznogoud', NULL, 'Place du Calife', NULL);
INSERT INTO client VALUES (3, 'Martin', 'Isabelle', 'Rue des Cerises', 0561616161);
INSERT INTO client VALUES (4, 'Martin', 'Celine', 'Rue des Tilleuls', 0534343434);
INSERT INTO client VALUES (5, 'Durand', 'Alain', 'Rue de la Colombette', 0561626262);
INSERT INTO client VALUES (10, 'Croquant', 'J.', 'Le bois qui tue', NULL);
INSERT INTO client VALUES (6, 'Durand', 'Alain', 'Rue Camichel', 0561585858);

INSERT INTO produit VALUES (1, 'Souris', 54.65, 'Souris 3 boutons');
INSERT INTO produit VALUES (2, 'Souris', 45.50, 'Souris 2 boutons');
INSERT INTO produit VALUES (3, 'Souris', 35.0, 'Souris 1 bouton');
INSERT INTO produit VALUES (4, 'Clavier', 125.0, 'Azerty');
INSERT INTO produit VALUES (5, 'Clavier', 130.0, 'Qwerty');
INSERT INTO produit VALUES (6, 'Ecran', 1200.0, 'Ecran 17p.');
INSERT INTO produit VALUES (7, 'Ecran', 800.0, 'Ecran 15p.');

INSERT INTO commande VALUES (1, 1, 3, '1999-10-30');
INSERT INTO commande VALUES (1, 1, 4, '1999-11-30');
INSERT INTO commande VALUES (1, 1, 1, '1999-09-10');
INSERT INTO commande VALUES (2, 1, 45, '2000-01-10');
