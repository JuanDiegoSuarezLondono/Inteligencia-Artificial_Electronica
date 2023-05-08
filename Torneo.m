function [PobSel ] = Torneo(Pob 2,ff)

[R, C] = size(Pob 2);

idx = zeros(1,R/2);

t = randperm(R);
tc = reshape(t,R/2,2);

for i = 1: R/2
    if (ff(fc(i,1)) < ff(fc(i,2)))
        idx(i) = fc(i,1);
    else
        idx(i) = fc(i,2);
    end

end
PobSel = Pob 2(idx,:);

end