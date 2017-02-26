function y  = moments(x)
y = zeros(1,3);
for i = 1:3
    y(1, i) = sum(x.^i)/length(x);
end
end
