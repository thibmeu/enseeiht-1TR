CREATE SEQUENCE "personne_num_per_seq" start 6 increment 1 maxvalue 2147483647 minvalue 1  cache 1 ;
GRANT ALL on "personne_num_per_seq" to PUBLIC;
SELECT nextval ('"personne_num_per_seq"');

CREATE SEQUENCE "c_d_num_cd_seq" start 6 increment 1 maxvalue 2147483647 minvalue 1  cache 1 ;
GRANT ALL on "c_d_num_cd_seq" to PUBLIC;
SELECT nextval ('"c_d_num_cd_seq"');

CREATE TABLE "personne" (
	"num_per" int4 DEFAULT nextval('personne_num_per_seq'::text) NOT NULL,
	"nom" character varying(40) NOT NULL,
	"tel" character varying(10),
	CONSTRAINT pk_pers PRIMARY KEY ("num_per")
);
REVOKE ALL on "personne" from PUBLIC;
GRANT ALL on "personne" to PUBLIC;

CREATE TABLE "c_d" (
	"num_cd" int4 DEFAULT nextval('c_d_num_cd_seq'::text) NOT NULL,
	"auteur" character varying(40) NOT NULL,
	"titre" character varying(60),
	"prop" int4 NOT NULL,
	CONSTRAINT pk_cd PRIMARY KEY ("num_cd")
);
REVOKE ALL on "c_d" from PUBLIC;
GRANT ALL on "c_d" to PUBLIC;



CREATE TABLE  emprunt ( num_cd INTEGER NOT NULL, num_p INTEGER NOT NULL, 
	CONSTRAINT pk_emp PRIMARY KEY(num_cd,num_p),
        CONSTRAINT fk_cd FOREIGN KEY(num_cd) REFERENCES c_d(num_cd),
	CONSTRAINT fk_pers FOREIGN KEY(num_p) REFERENCES personne(num_per));
REVOKE ALL on "emprunt" from PUBLIC;
GRANT ALL on "emprunt" to PUBLIC;

COPY "personne" FROM stdin;
1	Dupont	\N
2	Durand	0561616161
3	La Joie	0561101010
4	Doudou	\N
5	Mimi	0562626262
0	Amiga	\N
6	Pipite	0160666666
\.

COPY "c_d" FROM stdin;
1	La Tordue	\N	3
2	Bratsch	Notes de Voyages	1
3	Zebda	Essence Ordinaire	2
4	Anne Vanderlove	Liberte	1
5	Les Ogres de Barback	Rue du Temps	2
6	Gerard Manset	La Mort d Orion	5
\.

COPY "emprunt" FROM stdin;
1	1
2	2
1	2
1	4
\.

CREATE CONSTRAINT TRIGGER "fk_prop" AFTER DELETE ON "personne"  NOT DEFERRABLE INITIALLY IMMEDIATE FOR EACH ROW EXECUTE PROCEDURE "RI_FKey_noaction_del" ('fk_prop', 'c_d', 'personne', 'UNSPECIFIED', 'prop', 'num_per');

CREATE CONSTRAINT TRIGGER "fk_prop" AFTER UPDATE ON "personne"  NOT DEFERRABLE INITIALLY IMMEDIATE FOR EACH ROW EXECUTE PROCEDURE "RI_FKey_noaction_upd" ('fk_prop', 'c_d', 'personne', 'UNSPECIFIED', 'prop', 'num_per');

CREATE CONSTRAINT TRIGGER "fk_pers" AFTER DELETE ON "personne"  NOT DEFERRABLE INITIALLY IMMEDIATE FOR EACH ROW EXECUTE PROCEDURE "RI_FKey_noaction_del" ('fk_pers', 'emprunt', 'personne', 'UNSPECIFIED', 'num_p', 'num_per');

CREATE CONSTRAINT TRIGGER "fk_pers" AFTER UPDATE ON "personne"  NOT DEFERRABLE INITIALLY IMMEDIATE FOR EACH ROW EXECUTE PROCEDURE "RI_FKey_noaction_upd" ('fk_pers', 'emprunt', 'personne', 'UNSPECIFIED', 'num_p', 'num_per');

CREATE CONSTRAINT TRIGGER "fk_prop" AFTER INSERT OR UPDATE ON "c_d"  NOT DEFERRABLE INITIALLY IMMEDIATE FOR EACH ROW EXECUTE PROCEDURE "RI_FKey_check_ins" ('fk_prop', 'c_d', 'personne', 'UNSPECIFIED', 'prop', 'num_per');

CREATE CONSTRAINT TRIGGER "fk_cd" AFTER DELETE ON "c_d"  NOT DEFERRABLE INITIALLY IMMEDIATE FOR EACH ROW EXECUTE PROCEDURE "RI_FKey_noaction_del" ('fk_cd', 'emprunt', 'c_d', 'UNSPECIFIED', 'num_cd', 'num_cd');

CREATE CONSTRAINT TRIGGER "fk_cd" AFTER UPDATE ON "c_d"  NOT DEFERRABLE INITIALLY IMMEDIATE FOR EACH ROW EXECUTE PROCEDURE "RI_FKey_noaction_upd" ('fk_cd', 'emprunt', 'c_d', 'UNSPECIFIED', 'num_cd', 'num_cd');

CREATE CONSTRAINT TRIGGER "fk_cd" AFTER INSERT OR UPDATE ON "emprunt"  NOT DEFERRABLE INITIALLY IMMEDIATE FOR EACH ROW EXECUTE PROCEDURE "RI_FKey_check_ins" ('fk_cd', 'emprunt', 'c_d', 'UNSPECIFIED', 'num_cd', 'num_cd');

CREATE CONSTRAINT TRIGGER "fk_pers" AFTER INSERT OR UPDATE ON "emprunt"  NOT DEFERRABLE INITIALLY IMMEDIATE FOR EACH ROW EXECUTE PROCEDURE "RI_FKey_check_ins" ('fk_pers', 'emprunt', 'personne', 'UNSPECIFIED', 'num_p', 'num_per');
