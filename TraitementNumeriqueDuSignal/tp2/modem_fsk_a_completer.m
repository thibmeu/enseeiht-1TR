%Réalisation d'un modulateur/démodulateur de fréquences simplifié
%Fichier à compléter
%Février 2011

clear all
close all

%Paramètres
Fe=48000;   %Fréquence d'échantillonnage
F0=980;     %Fréquence du cosinus représentant le bit 0
F1=4080;    %Fréquence du cosinus représentant le bit 1
Ns=100;     %Nombre de points par symbole physique 
            %associé à un bit à transmettre
SNR_dB=100; %SNR souhaité donné en dB

%Génération de la suite de bits 0, 1 correpondant au texte à envoyer
X = str2bin('entrer ici le texte à envoyer');

%Génération de deux morceaux de cosinus comprenant Ns échantillons :
%cos0 pour coder le bit 0, de fréquence F0=980
cos0="à compléter";
%cos1 pour coder le bit 1, de fréquence F1=4080
cos1="à compléter";

%Modulation FSK : on remplace chaque bits 0 et 1 par un morceau de cosinus
%cos0 ou cos1
signal=kron(X.',cos1)+kron(abs(X.'-1),cos0);

%Tracé du signal
"à compléter"

%Canal : ajout de bruit, le SNR est fixé en dB dans les paramètres de
%départ
Pb="à déterminer pour avoir le SNR souhaité";
bruit=sqrt(Pb)*randn(1,length(signal));
signal_bruite=signal+bruit;

%Tracé du signal bruité et de son spectre
"à compléter"

%Génération de la réponse impulionnelle du filtre permettant de récupérer 
%les bits 1 en utilisant la fonction fir1 de matlab (!!mettre 2*Fc : cf help de fir1)
B="à compléter";
%Tracé de la fonction de transfert du filtre et du spectre du signal
%superposés
"à compléter"
%Filtrage du signal pour récupérer les "1"
"à compléter"
%Tracé du signal de départ et du signal filtré
"à compléter"

%Génération de la réponse impulionnelle du filtre permettant de récupérer
%les bits 0 en utilisant la fonction fir1 de matlab (!!mettre 2*Fc : cf help de fir1)
B="à compléter";
%Tracé de la fonction de transfert du filtre et du spectre du signal
%superposés
"à compléter"
%Filtrage du signal pour récupérer les "0"
"à compléter"
%Tracé du signal de départ et du signal filtré
"à compléter"

%Reconstruction de l'information binaire
%On crée un vecteur de 0 de la longueur des bits émis (vecteur X) 
suite_binaire_reconstruite=zeros(1,length(X));
%A partir du signal filtré pour récupérer les "1", on calcule l'énergie 
%des symboles physiques consécutifs 
mat_uns=reshape(signal_uns,100,length(signal_uns)/100);
energie=sum(abs(mat_uns.^2));
%Si l'énergie d'un symbole est supérieure à un seuil fixé, on décide que le
%symbole en question correspond à un "1" (que l'on va placer à la position 
%correspondante dans le vecteur suite_binaire_reconstruite), sinon il 
%correspond à un "0".
seuil="à définir";
find(energie>seuil);
suite_binaire_reconstruite(find(energie>seuil))=1;
%Reconstruction du texte à partir de la suite de bits retrouvée
bin2str(suite_binaire_reconstruite)

%Calcul du TEB
TEB="à compléter"

