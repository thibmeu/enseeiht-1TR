%
clear all;
close all;

%%%
% 1. Modulation numerique
%%%


%%Generation de bits
%Nb est pair
Nb = 2*6;

%On genere Nb bits
bits = rand(1, Nb)>0.5;


%%Modulation BPSK
%On transforme cette suite de bits en suite de -1 pour 0 et 1 pour 1
bpsk = bits*2-1;

%On calcule la moyenne m des symboles
m = mean(bpsk);

%Puis la variance sigma2
sigma2 = var(bpsk);

%Et la puissance P
P = sigma2 + abs(m)^2;


%%Modulation QPSK
qpsk = zeros(1, Nb/2);
for k = 1:(Nb/2)
    %on teste les bits deux a deux
    if(bits(2*k-1:2*k) == [0, 0])
        qpsk(k) = exp(j*pi/4);
    end
    if(bits(2*k-1:2*k) == [0, 1])
        qpsk(k) = exp(3j*pi/4);
    end
    if(bits(2*k-1:2*k) == [1, 0])
        qpsk(k) = exp(7j*pi/4);
    end
    if(bits(2*k-1:2*k) == [1, 1])
        qpsk(k) = exp(5j*pi/4);
    end
end;

%On calcule la moyenne m des symboles
m = mean(qpsk);

%Puis la variance sigma2
sigma2 = var(qpsk);

%Et la puissance P
P = sigma2 + abs(m)^2;


%%%Trace de l'evolution en fonction de Nb
%Pour ce faire, on a place les fonctions de generation de symbole dans le
%fichier psk.m
x = 1:6;
mBpsk = zeros(1, length(x));
sigma2Bpsk = zeros(1, length(x));
mQpsk = zeros(1, length(x));
sigma2Qpsk = zeros(1, length(x));
for Nb = 10.^(x)
    [bpsk, qpsk] = psk(Nb);
    
    mBpsk(log10(Nb)) = mean(bpsk);
    sigma2Bpsk(log10(Nb)) = var(bpsk);
    
    mQpsk(log10(Nb)) = mean(qpsk);
    sigma2Qpsk(log10(Nb)) = var(qpsk);
end;

PBpsk = sigma2Bpsk + abs(mBpsk).^2;

mQpsk = (real(mQpsk)+imag(mQpsk))/2;
sigma2Qpsk = (real(sigma2Qpsk)+imag(sigma2Qpsk))/2;
PQpsk = sigma2Qpsk + abs(mQpsk).^2;

hold on;
%Trace des moyennes
semilogx(x, mBpsk, 'r');
semilogx(x, mQpsk, 'b');

%Trace les variances
semilogx(x, sigma2Bpsk, 'g');
semilogx(x, sigma2Qpsk, 'b');

%Trace les puissances
semilogx(x, PBpsk, 'o');
semilogx(x, PQpsk, 'y');
hold off;
%On remarque tout d'abord que pour les differentes puissances dependent
%essentiellement de la variance et non de la moyenne : leurs courbes sont
%tres rapprochees.
%De plus, la variance de la modulation QPSK est plus faible, ce qui rend
%les symboles moins distincts, d'ou une puissance moins elevee que pour la
%modulation BPSK


%%On trace desormais l'erreur quadratique moyenne
figure(2);clf
eqmBpsk = sigma2Bpsk ./ (mBpsk.^2);
eqmQpsk = sigma2Qpsk ./ (mQpsk.^2);

hold on;
loglog(x, eqmBpsk, 'b');
loglog(x, eqmQpsk, 'o');
hold off;
%Bien que leur puissance soit differente, les deux types de modulation on
%une erreur quadratique moyenne identique.
%Cela parrait coherent du fait de l'ajout d'un nouvel axe pour pouvoir
%differencier les nouveaux symboles.


%%%
%2 . Emission de symboles non equiprobables
%%%

%On utilise le fichier eqm
p1 = 0.7;
p0 = 1-p1;
epsilon = p1/p0;
mu = 0;     %moyenne du bruit
sigma2 = 1;  %Variance du bruit
[Pb,signal] = eqm(p1, mu, sigma2);
%PbTheo = 1/2*erfc(sqrt(1/(2*sigma)));
racine = sqrt(2/sigma2);
rapport = log(epsilon)/(2*racine);
PbTheo = p1*qfunc(racine-rapport) + p0*qfunc(racine+rapport);
Pb
PbTheo
%Les probabilite d'erreur theorique et calculee ne coincident pas

close all;
hold on;
%Histogramme normalise
nInter = floor(sqrt(length(signal)));
[counts, centers] = hist(signal, nInter);
bar(centers, counts/(length(signal)*(centers(1,2)-centers(1,1))));

%Densite de probabilite theorique
plot(centers, (normpdf(centers, mu+1, sqrt(sigma2))*p0 + normpdf(centers, mu-1, sqrt(sigma2))*p1));
hold off;