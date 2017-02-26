function [ePb,eeqm,evar] = eqm(mu, sigma)
nSimu = 3000;
nGenere = 10;
v = 1;
s = 2*v*round(rand(nSimu, nGenere)) - v;
n = randn(nSimu, nGenere) * sqrt(sigma) + mu;
r = s + n;
signal = mean(s < 0 & r > 0,2) + mean(s > 0 & r < 0,2);
% for i = 1:nSimu
%     P1 = mean(s(i, :) < 0 & r(i, :) > 0);
%     P2 = mean(s(i, :) > 0 & r(i, :) < 0);
%     signal(1, i) = P1 + P2;
% end;
% keyboard
PbTheo = 1/2*erfc(sqrt(1/(2*sigma)));
eeqm = var(signal)/(mean(signal)^2);
evar = var(signal);
ePb = mean(signal);
end