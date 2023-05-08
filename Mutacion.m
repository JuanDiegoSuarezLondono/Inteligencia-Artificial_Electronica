function [ Pob ] = Mutacion(Pob,L,prob)
[R C] = size(Pob);
Tgenes = R*C;
GenesMut = round(Tgenes*prob/100);
for i = 1:GenesMut
    fila = randi([1 R]); colum= randi([1 C]);
    Pob(fila, colum) = 1 - Pob(fila,colum);
end
end
