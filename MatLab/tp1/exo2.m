clear all;
close all;
clc;

N=1000;
x=rand(1000,1);
x=sort(x);
hist(x,30);
maxS=0;
for k=1:N
    maxS=max(maxS, abs(k/N-x(k)));
end
maxS