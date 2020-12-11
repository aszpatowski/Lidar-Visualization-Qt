#Piotr_Krupa_Lista6_zad.1

%I_0 jest sta�e (const)
d = 0.0004;                      % 0,4mm -> 0,0004m
lam = 0.0000005;                 % 0,0005mm -> 0,0000005m
L = [-4:0.1:4];    l=4;          % 4000 mm -> 4m
m = 1;

for i=1:length(L)
  y(i) = (lam*L(i)*m)/d;               %Po�o�enie jasnych pr��k�w
  I(i) = (cos((pi*d*y(i))/(lam*l)))^2; %Nat�enie �wiat�a
end; 

plot(y,I);
xlabel("y");
ylabel("I");
title("Nat�enie �wiat�a w do�wiadczeniue Younga dla fali o d�ugo�ci 0,0005mm");
clear;