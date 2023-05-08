
clear all; clc; format long
tic
N = 200;
V = 3;
L=12;
INTER_MAX = 20;
mut = 5;
 tspan = 0:0.01:4;
 w = 10; z = 0.5; 
 T1 = 0.2;
 Yd=tf(1,[T1 1])
 step(Yd,tspan)
 I = [0.4 0.6; 4 6;0 0.08];
 
 w1 = 1;
 z1 = 0.5;
 %[t, Yd] = ode45(@Primer_orden, tspan, [0], [], [T1]);
 PobReal = Poblacion(N,V,L);
kp = PobReal(1,1)
kd = PobReal(1,2)
ki = PobReal(1,3)
z1 = 0.5;
Y=tf([(w^2)*(kd) (w^2)*(kp) (w^2)*(ki)],[1 (2*z*w+w^2*kd) (w^2+w^2*kp) w^2*ki])
figure
step(Y,tspan,'Y');
hold on

 cont=1;
 while (cont <= INTER_MAX)
     ff= fcosto(Yd,N, PobReal);
     ff_aux(cont) = min(ff);
     PObSel=Seleccion(PobReal, ff);
     Pob_C=CruceR(PobSel, V);
     PobReal=[PobSel;Pob_C];
     PobReal=Mutacion(PobReal,I,mut);
     cont=cont+1;
 end
toc
ff=fcosto(Yd,N, PobReal);
[val_indx]=min(ff);
semilogy(ff_aux);
kp=PobReal(idx, 1)
ki=PobReal(idx, 2)
kd=PobReal(idx, 3)