function [P_10]=PobDec(P,L,V)
[R C]=size(P);
aux= 1;
for j=1:V
    P_10(:,j)=bin2dec(num2str(P(:,aux:L*j)));
    aux=aux+L;
end 
end