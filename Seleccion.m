function [ PobSel ] = Seleccion(Pob_2,ff)
 [R C]= size(Pob_2);
 [B,idx]= sort(ff);
 Pob_2 = Pob_2(idx,:);
 PobSel = Pob_2(1:R/2,:);
 end