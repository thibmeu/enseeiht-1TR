function y = signal_bawg(A, mu, sigma, nGenere)
nSimu = 100;
s = 2*A*round(rand(nSimu, nGenere)) - A;
bruit = randn(nSimu, nGenere) * sqrt(sigma) + mu;
y = s + bruit;
end