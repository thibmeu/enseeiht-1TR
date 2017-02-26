function [bpsk, qpsk] = psk(Nb)
%On genere Nb bits
bits = rand(1, Nb)>0.5;


%%Modulation BPSK
%On transforme cette suite de bits en suite de -1 pour 0 et 1 pour 1
bpsk = bits*2-1;

%%Modulation QPSK
qpsk = zeros(Nb/2, 1);
for k = 1:(Nb/2)
    %on teste les bits deux a deux
    if(bits(2*k-1:2*k) == [0, 0])
        qpsk(k) = exp(j*pi/4);
    end
    if(bits(2*k-1:2*k) == [0, 1])
        qpsk(k) = exp(3j*pi/4);
    end
    if(bits(2*k-1:2*k) == [1, 0])
        qpsk(k) = exp(7j*pi/4);
    end
    if(bits(2*k-1:2*k) == [1, 1])
        qpsk(k) = exp(5j*pi/4);
    end
end;
end