function [a]=fcosto(Yd,N, PobReal)
    for i=0:N
        fcosto(:,N)=(Yd-PobReal)^2;
    end
    a=sum(fcosto);
end