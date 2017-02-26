%R�alisation d'un modulateur/d�modulateur de fr�quences simplifi�
%Fichier � compl�ter
%F�vrier 2011

clear all
close all

%Param�tres
Fe=48000;   %Fr�quence d'�chantillonnage
F0=980;     %Fr�quence du cosinus repr�sentant le bit 0
F1=4080;    %Fr�quence du cosinus repr�sentant le bit 1
Ns=100;     %Nombre de points par symbole physique 
            %associ� � un bit � transmettre
SNR_dB=100; %SNR souhait� donn� en dB

%G�n�ration de la suite de bits 0, 1 correpondant au texte � envoyer
X = str2bin('entrer ici le texte � envoyer');

%G�n�ration de deux morceaux de cosinus comprenant Ns �chantillons :
%cos0 pour coder le bit 0, de fr�quence F0=980
cos0="� compl�ter";
%cos1 pour coder le bit 1, de fr�quence F1=4080
cos1="� compl�ter";

%Modulation FSK : on remplace chaque bits 0 et 1 par un morceau de cosinus
%cos0 ou cos1
signal=kron(X.',cos1)+kron(abs(X.'-1),cos0);

%Trac� du signal
"� compl�ter"

%Canal : ajout de bruit, le SNR est fix� en dB dans les param�tres de
%d�part
Pb="� d�terminer pour avoir le SNR souhait�";
bruit=sqrt(Pb)*randn(1,length(signal));
signal_bruite=signal+bruit;

%Trac� du signal bruit� et de son spectre
"� compl�ter"

%G�n�ration de la r�ponse impulionnelle du filtre permettant de r�cup�rer 
%les bits 1 en utilisant la fonction fir1 de matlab (!!mettre 2*Fc : cf help de fir1)
B="� compl�ter";
%Trac� de la fonction de transfert du filtre et du spectre du signal
%superpos�s
"� compl�ter"
%Filtrage du signal pour r�cup�rer les "1"
"� compl�ter"
%Trac� du signal de d�part et du signal filtr�
"� compl�ter"

%G�n�ration de la r�ponse impulionnelle du filtre permettant de r�cup�rer
%les bits 0 en utilisant la fonction fir1 de matlab (!!mettre 2*Fc : cf help de fir1)
B="� compl�ter";
%Trac� de la fonction de transfert du filtre et du spectre du signal
%superpos�s
"� compl�ter"
%Filtrage du signal pour r�cup�rer les "0"
"� compl�ter"
%Trac� du signal de d�part et du signal filtr�
"� compl�ter"

%Reconstruction de l'information binaire
%On cr�e un vecteur de 0 de la longueur des bits �mis (vecteur X) 
suite_binaire_reconstruite=zeros(1,length(X));
%A partir du signal filtr� pour r�cup�rer les "1", on calcule l'�nergie 
%des symboles physiques cons�cutifs 
mat_uns=reshape(signal_uns,100,length(signal_uns)/100);
energie=sum(abs(mat_uns.^2));
%Si l'�nergie d'un symbole est sup�rieure � un seuil fix�, on d�cide que le
%symbole en question correspond � un "1" (que l'on va placer � la position 
%correspondante dans le vecteur suite_binaire_reconstruite), sinon il 
%correspond � un "0".
seuil="� d�finir";
find(energie>seuil);
suite_binaire_reconstruite(find(energie>seuil))=1;
%Reconstruction du texte � partir de la suite de bits retrouv�e
bin2str(suite_binaire_reconstruite)

%Calcul du TEB
TEB="� compl�ter"

