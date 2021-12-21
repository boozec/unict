f = @(x) normpdf(x, 5, 1);

x = -15:0.1:25;
y = f(x);
% plot(x, y);

% probability 'x' between 2 and 6
integral(f, 2, 6)

norminv(0.8, 5, 1)
integral(f, -inf, 5.8416) % ans = 0.8

% t-student
f1 = @(x) tpdf(x, 3);
f2 = @(x) tpdf(x, 8);

x = 0:0.1:10;
y1 = f1(x);
y2 = f2(x);

plot(x, y1, 'X', x, y2, 'O');

% Chi^2
f = @(x) chi2pdf(x, 60);
x = 1:0.01:100;
y = f(x);
plot(x, y);

% ----
u = (53.82 - 54.41) / sqrt(0.1/5+0.1/6);
norminv(1-0.05, 0, 1)