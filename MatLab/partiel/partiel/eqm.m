function [ePb,eR] = eqm(p, mu, sigma2)
q = 1-p;
nSimu = 100;
nGenere = 10*1000;
%On genere plusieurs signaux, valant -1 ou 1
v = 1;
s = 2*v*(rand(nSimu, nGenere) > p) - v;

%On genere egalement le bruit blanc gaussien
n = randn(nSimu, nGenere) * sqrt(sigma2) + mu;
%Puis on somlme les signaux
r = s + n;

%Le nouveau seuil pour des bits non equiprobable
seuil = sigma2*log(p/q)/4;
%Il y a une erreur si un 0 est devenu un 1 ou un 1 un 0
signal = mean(s < seuil & r >= seuil,2) + mean(s > seuil & r <= seuil,2);

ePb = mean(signal);
eR = r(1, :);
end