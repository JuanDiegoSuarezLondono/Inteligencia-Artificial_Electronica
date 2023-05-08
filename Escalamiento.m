function [Pob_float] = Escalamiento(Pob_10,I,V,L)
for i=1:V
    Pob_float(:,i)=Pob_10(:,i)/(2^L-1)*(I(i,2)-I(i,1))+I(i,1);
end
end