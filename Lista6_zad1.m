#Piotr_Krupa_Lista6_zad.1

%I_0 jest sta³e (const)
d = 0.0004;                      % 0,4mm -> 0,0004m
lam = 0.0000005;                 % 0,0005mm -> 0,0000005m
L = [-4:0.1:4];    l=4;          % 4000 mm -> 4m
m = 1;

for i=1:length(L)
  y(i) = (lam*L(i)*m)/d;               %Po³o¿enie jasnych pr¹¿ków
  I(i) = (cos((pi*d*y(i))/(lam*l)))^2; %Natê¿enie œwiat³a
end; 

plot(y,I);
xlabel("y");
ylabel("I");
title("Natê¿enie œwiat³a w doœwiadczeniue Younga dla fali o d³ugoœci 0,0005mm");
clear;