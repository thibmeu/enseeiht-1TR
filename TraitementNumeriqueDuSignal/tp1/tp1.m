clear all;
close all;

%%%
% 7.4.1 Autocorrelation d'un sinus bruite
%%%

N = 100;
fs = 18;
fe = 1000;
f = fs/fe;
SNR = -7;
mu = 0;
sigma2 = 1;

% Generation du signal en entree
x = 1:N;
signalEntree = sin(2*pi*f .* x);
% Generation d'un bruit blanc gaussien
bruit = randn(1, N) * sqrt(sigma2) + mu;
% Signal bruite
signalBruite = signalEntree + bruit;

% Autocorrelartion
R = xcorr(signalBruite, 'biased');

plot(R);

%%%
% 7.4.2 Transformee de Fourier numerique d'une sinusoide : effet du zero padding
%%%

N = 1000;
fs = 18;
fe = 1000;
f = fs/fe;
SNR = -7;
mu = 0;
sigma2 = 1;

% Generation du signal en entree
x = 1:N;
signalEntree = sin(2*pi*f .* x);
% Generation d'un bruit blanc gaussien
bruit = randn(1, N) * sqrt(sigma2) + mu;
% Signal bruite
signalBruite = signalEntree + bruit;

% Zero padding
figure();
hold on;
nfft = 2^nextpow2(N);
for iPadding = 1:10
    curfft = fft(signalBruite, nfft);
    x = 0:1/nfft:(1-1/nfft);
    plot(x, abs(curfft));
    nfft = nfft*2;
end;
hold off;