% lesson of nov 9th, 2021
% display a 3D plot

[X, Y] = meshgrid(-2*pi:0.1:2*pi, -4*pi:0.1:4*pi);
Z = sin(X) + cos(Y);

% surf(X, Y, Z);

Z = X.^2+Y.^2;
mesh(X, Y, Z);


xlabel('X');
ylabel('Y');
zlabel('Z');

% ---

T = readtable("speed-and-density.txt");
Y = table2array(T(:,1));
X = table2array(T(:,2));
plot(X, Y);
ylabel('Speed');
xlabel('Density');