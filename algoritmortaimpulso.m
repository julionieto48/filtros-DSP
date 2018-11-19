clc, clear all, close all;
%%
% implementar y(n) = x(n)+ 1.8 y(n-1)-0.5y(n-2)
h = [];
for (n = 1: 10)
    if (n == 1)
        h(n) = 1
    elseif (n == 2)  
        h(n) = 1.8* h(n-1)
    elseif (n > 2)
        n
        h_1(n) = h(n - 1)
        h2 (n) = h(n - 2)
        h(n) = 1.8* h(n-1) - 0.5* h(n -2)
        
    
    end
end