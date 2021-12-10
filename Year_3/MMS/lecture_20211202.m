f = @(x) x.^2;
x = 0:0.1:2;
y = f(x);
integral(f, 0, 1);

g = @(x) exp(-2 * x.^2);
integral(g, 1, inf);

% ---

load fish;
price70 = table2array(fish(:, 2));
xbar = mean(price70);
s = std(price70);

% Normal function
f = @(x) (1/s/sqrt(2*pi))*exp(-(x-xbar).^2/(s^2)/2);

integral(f, xbar, inf); % 0.5000

x = (xbar- 100):1.0:(xbar+100);
y = f(x);

% Integrated normal function
yy = normpdf(x, xbar, s);

% Plots are the same
% plot(x, yy, 'o', x, yy, '+')

ustemps = readtable("UStemps.txt");
jantemps = table2array(ustemps(:, 2));

% normrnd(0, 1);

tbar = mean(jantemps);
ds = std(jantemps);

norminv(0.5, tbar, ds); % with 0.5 you have the mean