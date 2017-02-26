function y = ber(mu, sigma)
nSimu = 10;
nGenere = 10*100;
v = 1;
s = 2*v*round(rand(nSimu, nGenere)) - v;
n = randn(nSimu, nGenere) * sqrt(sigma) + mu;
r = s + n;
signal = mean(s < 0 & r > 0) + mean(s > 0 & r < 0);
% for i = 1:nSimu
%     P1 = mean(s(i, :) < 0 & r(i, :) > 0);
%     P2 = mean(s(i, :) > 0 & r(i, :) < 0);
%     signal(1, i) = P1 + P2;
% end;
y = mean(signal);
end