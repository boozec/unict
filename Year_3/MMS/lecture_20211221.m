% First, import `regressione_lineare/brakes.txt` as Column vectors

% plot(Speedmph, StoppingDistance, 'o');

p = polyfit(Speedmph, StoppingDistance, 1); 
f = @(x) p(1)*x + p(2);

x = min(Speedmph)-1:0.1:max(Speedmph)+2;
y = f(x);

% plot(Speedmph, StoppingDistance, 'o', x, y);

% ---
% Import `regressione_lineare/boyle.txt` as Column vectors
x = Height;
y = Pressure;

xbar = mean(x);
ybar = mean(y);
n = length(x);

Sxx = 0.0;
Syy = 0.0;
Sxy = 0.0;

for i = 1:1:length(x)
    Sxx = Sxx + (x(i)-xbar)^2;
    Syy = Syy + (y(i)-ybar)^2;
    Sxy = Sxy + (x(i)-xbar) * (y(i)-ybar);
end

R2 = Sxy^2 / (Sxx*Syy);
SSRes = (Sxx*Syy - Sxy^2) / Sxx;
R2Corr = 1 - SSRes/Syy*(n-1)/(n-2);

% Import `regressione_lineare/all-the-efficiency.txt` as Column vectors
p = polyfit(EfficiencyhiwayMpg, MSRP, 1);

f = @(x) p(1)*x + p(2);
x = min(EfficiencyhiwayMpg)-1:0.1:max(EfficiencyhiwayMpg)+2;
y = f(x);

% plot(EfficiencyhiwayMpg, MSRP, 'o', x, y);
