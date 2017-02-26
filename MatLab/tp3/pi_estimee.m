function y = pi_estimee(signal, sigma, K)
N = length(signal');
alpha = 0.01:0.01:0.99;
y = zeros(1, length(alpha));
for i = 1:length(y)
    phiinv = norminv(alpha(1, i)./2);
    tmp = generer(signal, sigma, K);
    sigmaP = sqrt(signal'*(sigma^-1)*signal);
    seuil = -phiinv*sigmaP;
    R = zeros(1, K);
    for k = 1:K
        sigmaT = signal'*(sigma^-1)*tmp(k, :)';
        R(1, k) = abs(sigmaT) > seuil;
    end;
    y(1,i) = mean(R);
    %keyboard;
end;
end