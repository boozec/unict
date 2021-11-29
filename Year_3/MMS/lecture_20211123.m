fish = readtable("fish.txt");
p = table2array(fish(:, 2)); % Import the Price 1970 col from "fish.txt"

mean(p);
median(p);
min(p);
max(p);
range(p);

xvar = var(p);
xdev = std(p);
sqrt(xvar) == xdev; % Prints "1"

% ---
load("nations.mat");
MC = cov(nations);
size(MC);
data1 = nations(:, 1);
data2 = nations(:, 2);

corrcoef(data1, data2);

% plot(data1, data2, 'x');

load("T.mat");
Tarray = table2array(T);
sp = Tarray(:, 1);
dn = Tarray(:, 2);
corr = corrcoef(sp, dn);

disp(corr);
plot(sp, dn, 'x')
xlabel("Speed");
ylabel("Density");

load earth;
histogram(earth);
histfit(earth);
quantile(earth, 2);
