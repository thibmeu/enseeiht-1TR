clear all;
close all;
clc;

N=1000;
nC=randn(N, 1);
m=2;
v=4;
sigma=sqrt(v);

y=nC*sigma+m;
nbIntervalles=30;
histfit(y,nbIntervalles);
close all;
a=norminv(0.25, m, sigma);
b=norminv(0.75, m, sigma);
z1=sum(y<a)
z2=sum(y>a & y<m)
z3=sum(y>m & y<b)
z4=sum(y>b)

chi=((z1-N*0.25)^2+(z2-N*0.25)^2+(z3-N*0.25)^2+(z4-N*0.25)^2)/(N*0.25)
testChi=chi<chi2inv(0.5,4-1)
[h,p,stats] = chi2gof(y,'cdf',{@normcdf,mean(y),std(y)})