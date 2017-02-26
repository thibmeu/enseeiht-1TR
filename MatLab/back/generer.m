function y = generer(signal, sigma, K)
N = length(signal');
mu = 0;
y = zeros(K, N);
for i = 1:K
    theta = 2*randi(2)-3;
    bruit = randn(1, N) * sqrt(sigma(1)) + mu;
    y(i, :) = theta*signal'+bruit;
end;
end