function AG1
clear all
clc
N=input('N: ');
L=input('L: ');
V =input('V: ');
Epsilon =input('Epsilon: ');
prob =input('prob: '); 
ITER_MAX = input('INTERMax: ');;
I = [-5 5; -5 5; -5 5];
Pob_2 = Poblacion(N,L,V);
Pob_10= PobDec(Pob_2,L,V);
Pob_real = Escalamiento(Pob_10,I,V,L);
cont = 1;
ff_aux = 1000;

    while ((cont <= ITER_MAX) && (ff_aux > Epsilon))
        ff = (Pob_real).^2;
        plot(Pob_real,ff);
        PobSel_2 = Seleccion(Pob_2,ff);
        Pob_C = Cruce(PobSel_2,L,V);
        Pob_2 = [PobSel_2;Pob_C];
        Pob_2 = Mutacion(Pob_2,L,prob);
        Pob_10= PobDec(Pob_2,L,V);
        Pob_real = Escalamiento(Pob_10,I,V,L);
        [ff_aux, idy] = min(ff);
        cont = cont+1;
    end
end