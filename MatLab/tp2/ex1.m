function y  = moments(x)
for i = 1:3
    y = sum(x.^i)/length(x);
end
end
