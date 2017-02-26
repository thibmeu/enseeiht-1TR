%Realisation d'un modulateur/demodulateur de frequences simplifie
%Fichier a completer
%Fevrier 2011

clear all;
close all;

%Parametres
Fe=48000;   %Frequence d'echantillonnage
F0=980;     %Frequence du cosinus representant le bit 0
F1=4080;    %Frequence du cosinus representant le bit 1
Ns=100;     %Nombre de points par symbole physique 
            %associe e un bit e transmettre
SNR_dB=100; %SNR souhaite donne en dB

%Generation de la suite de bits 0, 1 correpondant au texte e envoyer
X = str2bin('H');

%Generation de deux morceaux de cosinus comprenant Ns echantillons :
%cos0 pour coder le bit 0, de frequence F0=980
cos0=cos(2*pi*F0/Fe*[0:100]);
%cos1 pour coder le bit 1, de frequence F1=4080
cos1=cos(2*pi*F1/Fe*[0:100]);

%Modulation FSK : on remplace chaque bits 0 et 1 par un morceau de cosinus
%cos0 ou cos1
signal=kron(X.',cos1)+kron(abs(X.'-1),cos0);
numel(signal)

%Puissance du signal
Ps=mean(abs(signal).^2);

%Trace du signal
hold on;
abscisse = linspace(0, 1/Fe, length(signal));
plot(abscisse, signal);

%Canal : ajout de bruit, le SNR est fixe en dB dans les parametres de
%depart
Pb=Ps*10^(-SNR_dB/10);
bruit=sqrt(Pb)*randn(1,length(signal));
signal_bruite=signal+bruit;

%Trace du signal bruite et de son spectre
plot(abscisse, signal_bruite);
hold off;

%Definition de la frequence de coupure
Fc=2500;
%Generation de la reponse impulionnelle du filtre permettant de recuperer 
%les bits 1 en utilisant la fonction fir1 de matlab (!!mettre 2*Fc : cf help de fir1)
nbCoeff=100;
B1=fir1(nbCoeff, 2*Fc/Fe, 'high');
%Trace de la fonction de transfert du filtre et du spectre du signal
%superposes
hold on;
nfft=2^nextpow2(length(signal_bruite));
Y=abs(fft(signal_bruite, nfft));
abscisseNorm=0:1/length(Y):(1-1/length(Y));
plot(abscisseNorm, Y);
hold off;
%Filtrage du signal pour recuperer les "1"
signal_filtre1=filter(B1, 1, [signal_bruite, zeros(1, nbCoeff/2)]);
%Trace du signal de depart et du signal filtre
close all;
hold on;
plot(abscisse, signal_bruite);
plot(abscisse, signal_filtre1(nbCoeff/2+1:end));
hold off;

%Generation de la reponse impulionnelle du filtre permettant de recuperer
%les bits 0 en utilisant la fonction fir1 de matlab (!!mettre 2*Fc : cf help de fir1)
B0=fir1(nbCoeff, 2*Fc/Fe, 'low');
%Trace de la fonction de transfert du filtre et du spectre du signal
%superposes
hold on;
plot(abscisseNorm, Y);
hold off;
%Filtrage du signal pour recuperer les "0"
signal_filtre0=filter(B0, 1, [signal_bruite, zeros(1, nbCoeff/2)]);
%Trace du signal de depart et du signal filtre
close all;
hold on;
plot(abscisse, signal_bruite);
plot(abscisse, signal_filtre0(nbCoeff/2+1:end));
hold off;

%Reconstruction de l'information binaire
%On cree un vecteur de 0 de la longueur des bits emis (vecteur X) 
suite_binaire_reconstruite=zeros(1,length(X));
%A partir du signal filtre pour recuperer les "1", on calcule l'energie 
%des symboles physiques consecutifs 
signal_uns=[signal_filtre1, zeros(1, 42)];
mat_uns=reshape(signal_uns,100,length(signal_uns)/100);
energie=sum(abs(mat_uns.^2));
%Si l'energie d'un symbole est superieure e un seuil fixe, on decide que le
%symbole en question correspond e un "1" (que l'on va placer e la position 
%correspondante dans le vecteur suite_binaire_reconstruite), sinon il 
%correspond e un "0".
seuil=10;
find(energie>seuil);
suite_binaire_reconstruite(find(energie>seuil))=1;
%Reconstruction du texte e partir de la suite de bits retrouvee
Y=bin2str(suite_binaire_reconstruite)

%Calcul du TEB
TEB=1-mean(X == Y)
