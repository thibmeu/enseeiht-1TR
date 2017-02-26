close all;
clear all;

%%%
%% I. Chaine de transmissions pour modulation PAM à 2 états, mise en forme rectangulaire
%%%

%% Emetteur
N = 1000; % Nombre de bits
M = 2; % Les bits valent 0 ou 1
% On genere des 0 et des 1 equiprobables et independants
bits = round(rand(1, N));
% On les repartis en -1/1
a = bits.*M-(M/2);

n = 10; % Nombre d'echantillons sur une duree symboles
Te = 1;
Ts = n;
% On cree le peigne de diracs
peigne = kron(a, [1, zeros(1, n-1)]);

% Forme d'onde rectangulaire de duree Ts
h = ones(1,Ts)./sqrt(Ts);
% Mise en forme en sortie de l'emetteur
emis = filter(h, 1, peigne);

%% Canal
EbN0 = 10.^((1:0.1:6)./10); % Rapport signal a bruit par bits a l'entree du recepteur
% Calcul de la puissance du bruit
sigman2=sum(abs(h).^2)*var(a)./(2*log2(M)*EbN0);
% On determine le bruit
awgn = randn(length(EbN0), length(peigne));
awgn = awgn .* (sqrt(sigman2')*ones(1,length(awgn)));
% On simule le signal bruite
bruite = bsxfun(@plus, awgn, emis);

%% Recepteur
%%% Sans bruit
% Pour un filtre adapte, on reutilise le meme filtre que celui de mise en
% forme
hr = h;
recu = filter(h, 1, bruite')';
% Affichage du signal recu
figure('Name', 'Signaux recus');
plot(recu(end, :));
hold on;
plot(emis);
title('Signal recu / Signal emis');
legend('Signal recu', 'Signal emis');
xlabel('Echantillon');
ylabel('Amplitude');
hold off;
%Diagramme de l'oeil
figure('Name', 'Diagramme de l oeil')
plot(reshape(recu(end,:),Ts,length(recu)/Ts));
title('Diagramme de l oeil')
xlabel('Echantillon')
ylabel('Amplitude')
% Decision
t0=Ts;
symbolesRecus = recu(:, t0:Ts:end);
% Mapping
bitsRecus = symbolesRecus > 0;

%%% Avec bruit
% TEB theorique
TEBTheo = 2*(M-1)/M.*qfunc(sqrt(6*log2(M)/(M^2-1)*EbN0));

% TEB pratique
TEBCal = mean(bsxfun(@ne, bits, bitsRecus), 2)';

figure('Name', 'Comparaison des TEB');
semilogy(10*log10(EbN0), TEBTheo, 'blue');
hold on;
semilogy(10*log10(EbN0), TEBCal, 'red');
legend('TEB Theorique', 'TEB Calcule');
xlabel('Eb/N0 (dB)');
ylabel('TEB');
title('Comparaison des TEB');
hold off;

%%%
%% II. Chaine de transmissions pour modulation PAM à 2 états, effet d'un filtrage non adapte
%%%
% On genere hr comme h contracte de 50%
hr = h(1:2:end);
hr(length(h)) = 0;

recu = filter(h, 1, bruite')';
% Affichage du signal recu
figure('Name', 'Signaux recus');
plot(recu(end, :));
hold on;
plot(emis);
title('Signal recu / Signal emis');
legend('Signal recu', 'Signal emis');
xlabel('Echantillon');
ylabel('Amplitude');
hold off;
%Diagramme de l'oeil
figure('Name', 'Diagramme de l oeil')
plot(reshape(recu(end,:),Ts,length(recu)/Ts));
title('Diagramme de l oeil')
xlabel('Echantillon')
ylabel('Amplitude')
% Decision
t0=Ts;
symbolesRecus = recu(:, t0:Ts:end);
% Mapping
bitsRecus = symbolesRecus > 0;

%%% Avec bruit
% TEB theorique
TEBTheo = 2*(M-1)/M.*qfunc(sqrt(6*log2(M)/(M^2-1)*EbN0));

% TEB pratique
TEBCal = mean(bsxfun(@ne, bits, bitsRecus), 2)';

figure('Name', 'Comparaison des TEB');
semilogy(10*log10(EbN0), TEBTheo, 'blue');
hold on;
semilogy(10*log10(EbN0), TEBCal, 'red');
legend('TEB Theorique', 'TEB Calcule');
xlabel('Eb/N0 (dB)');
ylabel('TEB');
title('Comparaison des TEB');
hold off;


%%%
%% III. Chaîne de transmission pour modulation PAM à 2 états, mise en forme en racine de cosinus surélevé
%%%

%%% Sans Bruit
% Forme d'onde rectangulaire de duree Ts
rollHoff = 0.5;
ordre = 16;
h = rcosdesign(rollHoff,ordre,n, 'sqrt');
retard = length(h)-1; % car on ne compte pas l'echantillon central
% Mise en forme en sortie de l'emetteur
emis = filter(h, 1, peigne);

%% Canal
EbN0 = 10.^((0:1:6)./10); % Rapport signal a bruit par bits a l'entree du recepteur
% Calcul de la puissance du bruit
sigman2=sum(abs(h).^2)*var(a)./(2*log2(M)*EbN0);
% On determine le bruit
awgn = randn(length(EbN0), length(peigne));
awgn = awgn .* (repmat(sqrt(sigman2'),1,length(awgn)));
% On simule le signal bruite
% bruite = bsxfun(@plus, zeros(size(awgn)), emis);
bruite = bsxfun(@plus, awgn, emis);
% On effectue du zero padding pour recuperer les echantillons retardes
bruite(end, end+retard) = 0;

%% Recepteur
%%% Sans bruit
% Pour un filtre adapte, on reutilise le meme filtre que celui de mise en
% forme
hr = h;
recu = filter(h, 1, bruite')';
% Affichage du signal recu
figure('Name', 'Signaux recus');
plot(recu(end, :));
hold on;
plot(emis);
title('Signal recu / Signal emis');
legend('Signal recu', 'Signal emis');
xlabel('Echantillon');
ylabel('Amplitude');
hold off;
%Diagramme de l'oeil
figure('Name', 'Diagramme de l oeil')
plot(reshape(recu(end,:),Ts,length(recu)/Ts));
title('Diagramme de l oeil')
xlabel('Echantillon')
ylabel('Amplitude')
% Decision
t0=1;
symbolesRecus = recu(:, (t0+retard):Ts:end);
% Mapping
bitsRecus = symbolesRecus > 0;

% TEB theorique
TEBTheo = 2*(M-1)/M.*qfunc(sqrt(6*log2(M)/(M^2-1)*EbN0));

% TEB pratique
TEBCal = mean(bsxfun(@ne, bits, bitsRecus), 2)';

figure('Name', 'Comparaison des TEB');
semilogy(10*log10(EbN0), TEBTheo, 'blue');
hold on;
semilogy(10*log10(EbN0), TEBCal, 'red');
legend('TEB Theorique', 'TEB Calcule');
xlabel('Eb/N0 (dB)');
ylabel('TEB');
title('Comparaison des TEB');
hold off;

%%% Etude de l'impact du roll off
% Un roll off eleve entraine une precision moins bonne (on s'eloigne du modele ideal : la porte)
% Mais un roll off faible oblige a prendre plus de coefficient du fait de
% la repartition de l'energie dans les lobes lateraux

%%% Canal a bande limite
% A faire


%%%
%% IV. Chaîne de transmission pour modulation PAM à 2 états, mise en forme rectangulaire, canal avec ISI
%%%

%%% Sans Bruit
% Forme d'onde rectangulaire de duree Ts
h = ones(1,Ts)./sqrt(Ts);
% Mise en forme en sortie de l'emetteur
emis = filter(h, 1, peigne);

%% Canal
retard1 = 0;
a1 = 1;
retard2 = Ts;
a2 = 0.5;
d_ret = abs(retard1-retard2); % delta retard: difference entre les deux signaux
multitrajet = a2*[zeros(1, d_ret), emis] + a1*[emis, zeros(1, d_ret)];

EbN0 = 10.^((0:1:6)./10); % Rapport signal a bruit par bits a l'entree du recepteur
% Calcul de la puissance du bruit
sigman2=sum(abs(h).^2)*var(a)./(2*log2(M)*EbN0);
% On determine le bruit
awgn = randn(length(EbN0), length(multitrajet));
awgn = awgn .* (repmat(sqrt(sigman2'),1,length(awgn)));
% On simule le signal bruite
% bruite = bsxfun(@plus, zeros(size(awgn)), multitrajet); % si on veut enlever le bruit
bruite = bsxfun(@plus, awgn, multitrajet);

%% Recepteur
%%% Sans bruit
% Pour un filtre adapte, on reutilise le meme filtre que celui de mise en
% forme
hr = h;
recu = filter(h, 1, bruite')';
figure('Name', 'Signaux recus');
plot(recu(end, :));
hold on;
plot(emis);
title('Signal recu / Signal emis');
legend('Signal recu', 'Signal emis');
xlabel('Echantillon');
ylabel('Amplitude');
hold off;
%Diagramme de l'oeil
figure('Name', 'Diagramme de l oeil')
plot(reshape(recu(end,:),Ts,length(recu)/Ts));
title('Diagramme de l oeil')
xlabel('Echantillon')
ylabel('Amplitude')

% Decision
t0 = Ts; % En fait Ts/2, mais pour avoir le bon indice dans le tableau
symbolesRecus = recu(:, t0:Ts:end);
% Mapping a      0  Ts
% Si +1.5 alors  1  1
% Si +0.5 alors  1  0
% Si -0.5 alors  0  1
% Si -1.5 alors  0  0
bitsRecus1 = symbolesRecus(:, 1:(end-1)) > 0;
bitsRecus2 = symbolesRecus > 1 | (symbolesRecus <= 0 & symbolesRecus > -1);
bitsRecus2 = bitsRecus2(:, 2:end);
bitsRecus2(:, end) = symbolesRecus(:, end-1) > 0;

% TEB theorique
TEBTheo = (M-1)/M.*(qfunc(0.5*sqrt(6*log2(M)/(M^2-1)*EbN0)) + qfunc(1.5*sqrt(6*log2(M)/(M^2-1)*EbN0)));

% TEB pratique
TEBCal1 = mean(bsxfun(@ne, bits, bitsRecus1), 2)';
TEBCal2 = mean(bsxfun(@ne, bits, bitsRecus2), 2)';

figure('Name', 'Comparaison des TEB');
semilogy(10*log10(EbN0), TEBTheo, 'blue');
hold on;
semilogy(10*log10(EbN0), TEBCal1, 'red');
% semilogy(10*log10(EbN0), TEBCal2, 'green');
legend('TEB Theorique', 'TEB Calcule 1');
xlabel('Eb/N0 (dB)');
ylabel('TEB');
title('Comparaison des TEB');
hold off;