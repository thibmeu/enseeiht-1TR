function y = pi_theorique(signal, sigma)
alpha = 0.01:0.01:0.99;
sigma = sqrt(signal'*(sigma^-1)*signal);
Ba = normcdf(-norminv(alpha./2)+sigma)-normcdf(norminv(alpha./2)+sigma);
y = 1-Ba;
end