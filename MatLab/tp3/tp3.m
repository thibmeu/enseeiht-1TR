%
clear all
%Genere lance de
lance1 = floor(rand()*6+1);
lance2 = randi(6);

%Variable de Bernoulli
nGenere = 10000;
p = 0.2;
bernoulliG = mybernoulli(p, nGenere);
esperanceBer = mean(bernoulliG);
varianceBer = var(bernoulliG);

%Variable binomiale
n = 10;
binomiale = zeros(1, nGenere);
for i = 1:nGenere
    binomiale(1, i) = sum(mybernoulli(p, n));
end
esperanceBin = mean(binomiale);
varianceBin = var(binomiale);

%Variable uniforme
uniforme = rand(1, nGenere);

%Trace de l'histogramme
nInter = floor(sqrt(nGenere));
hist(uniforme);

%Densite de probabilite
[counts, centers] = hist(uniforme, nInter);
bar(centers, counts/(nGenere*1/nInter));

%Densite reele
hold on;
plot(centers, ones(1, size(centers, 2)));
hold off;

%Variable Gaussienne
mu = 0;
sigma = 1;
gaussian = randn(1, nGenere) * sqrt(sigma) + mu;

%Trace de l'histogramme
hist(gaussian, nInter);

%Densite de probabilite
[counts, centers] = hist(gaussian, nInter);
bar(centers, counts/(nGenere*(centers(1,2)-centers(1,1))));

%Densite reele
hold on;
plot(centers, normpdf(centers, mu, sigma));
hold off;

%%
%5. Transmission de bits
%%
%Variable uniforme
a = -3;
b = -a;
N = 1000*1000;
uniforme = (b-a)*rand(1, N)-b;

%Trace de l'histogramme
nInter = floor(sqrt(nGenere));
hist(uniforme);

%Densite de probabilite
[counts, centers] = hist(uniforme, nInter);
bar(centers, counts/(nGenere*1/nInter));

%Densite reele
hold on;
plot(centers, ones(1, size(centers, 2)));
hold off;

%Generation du signal a transmettre
nGenere = 10 * 1000;
v = 5;
s = 2*v*round(rand(1, nGenere)) - v;

%Coreelation entre deux variables aleatoires gaussiennes
mu = 0;
sigma = 0.2;
g1 = randn(1, nGenere) * sqrt(sigma) + mu;
g2 = randn(1, nGenere) * sqrt(sigma) + mu;
covariance = cov(g1, g2);

%Generation du signal en sortie
mu = 0;
sigma = 1;
n = randn(1, nGenere) * sqrt(sigma) + mu;
r = s + n;

%Trace de l'histogramme
nInter = floor(sqrt(nGenere));
hist(r, nInter);

%Densite de probabilite
[counts, centers] = hist(r, nInter);
bar(centers, counts/(nGenere*(centers(1,2)-centers(1,1))));

%Densite reele
hold on;
plot(centers, (normpdf(centers, mu - v, sqrt(sigma)) + normpdf(centers, mu + v, sqrt(sigma)))/2);
hold off;

%si r < 0, b = -v, sinon, b = v;
hist(r > 0, 2);

%Symbole
nGenere = 10 * 1000;
nInter = floor(sqrt(nGenere));
s = 2*round(rand())-1+j*(2*round(rand())-1);
mu = 0;
sigma = 1;
nc = randn(1, nGenere) * sqrt(sigma/2) + mu;
ns = j*(randn(1, nGenere) * sqrt(sigma/2) + mu);
n = nc + ns;
r = s + n;
hist3([[real(r)].', [imag(r)].'], [nInter/2, nInter/2]);

%Canal avec gain suivant une loi de Rayleigh
nGenere = 10 * 1000;
nInter = floor(sqrt(nGenere));
s = 2*round(rand())-1+j*(2*round(rand())-1);
mu = 0;
sigma = 1;
nc = randn(1, nGenere) * sqrt(sigma/2) + mu;
ns = j*(randn(1, nGenere) * sqrt(sigma/2) + mu);
n = nc + ns;
p = raylrnd(1);
theta = 2*pi*rand();
h = p*exp(j*theta);
r = h*s + n;
hist3([[real(r)].', [imag(r)].'], [nInter/2, nInter/2]);


%Generation du signal a transmettre
nSimu = 100;
nGenere = 10*1000;
v = 1;
s = 2*v*round(rand(nSimu, nGenere)) - v;

%Generation du signal en sortie
mu = 0;
sigma = 0.1;
n = randn(nSimu, nGenere) * sqrt(sigma) + mu;
r = s + n;

%Trace de l'histogramme
nInter = floor(sqrt(nGenere));
hist(r(1, :), nInter);

%Densite de probabilite
[counts, centers] = hist(r(1, :), nInter);
bar(centers, counts/(nGenere*(centers(1,2)-centers(1,1))));

%Densite reele
hold on;
plot(centers, (normpdf(centers, mu - v, sqrt(sigma)) + normpdf(centers, mu + v, sqrt(sigma)))/2);
hold off;
% 
% %P1 : Emmetre 0 et recevoir 1
% signal = zeros(1, nSimu);
% for i = 1:nSimu
%     P1 = mean(s(i, :) < 0 & r(i, :) > 0);
%     P2 = mean(s(i, :) > 0 & r(i, :) < 0);
%     signal(1, i) = P1 + P2;
% end;
% P1 = mean(s < 0 & r > 0);
% 
% %P2 : Emmetre 1 et recevoir 0
% P2 = mean(s > 0 & r < 0);
% 
% %Pb : Probabilite d'erreur binaire
% Pb = mean(signal);
% Pb
% 
% %Pb theorique
% PbTheo = 1/2*erfc(sqrt(1/(2*sigma)));
% PbTheo
% 
% %Variance des resultats
% vari = var(signal);
% vari
% 
% %Variance theorique
% varTheo = PbTheo*(1-PbTheo)/nGenere;
% varTheo
% 
% %Erreur quadratique moyenne
% % erreurqm = std2(Pb - PbTheo);
% erreurqm = vari/(Pb^2);
% erreurqm
% 
% %Trace du BER en fonction de 1/sigma^2 BER = f(1/sigma)
% mu = 0;
% lsig2 = -2:0.2:2;
% sigma = 10.^(lsig2);
% berPlot = zeros(1, length(sigma));
% eqmPlot = zeros(1, length(sigma));
% for i = 1:length(sigma)
%     %disp(i);
%     %berPlot(1,i) = ber(mu, sigma(1,i));
%     [c,a,b] = eqm(mu, sigma(1, i));
%     eqmPlot(1, i)=a;
%     varPlot(1, i)=b;
%     berPlot(1,i)=c;
% end;
% 
% 
% close all;
% figure(1);clf
% errorbar(lsig2,berPlot,varPlot)
% 
% figure(2);clf
% plot(lsig2,log(eqmPlot))
% plot(sigma, berPlot,'b');
% plot(sigma, eqmPlot,'r');
% hold off;
% 

% %%
% %6. Detection de signal
% %%
% %Puissance theorique du test Neyman Person
% N = 20;
% s = sin(2*pi*0.1*(1:N));
% sigma = eye(N);
% alpha = 0.01:0.01:0.99;
% plot(alpha, pi_theorique(s', sigma));
% close all;
% hold on;
% plot(alpha, pi_theorique(s', sigma));
% plot(alpha, pi_theorique(s', 2*sigma));
% plot(alpha, pi_theorique(s', 3*sigma));
% %Generation d'un signal transmis sur canal avec bruit Gaussien
% generer(N, sigma, 20);
% 
% %Puissqnce estimee
% plot(alpha, pi_estimee(s', sigma, 500));
% plot(alpha, pi_estimee(s', 2*sigma, 500));
% plot(alpha, pi_estimee(s', 3*sigma, 500));