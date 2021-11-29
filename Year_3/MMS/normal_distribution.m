function fn = normal_distribution(data)
    mu = mean(data);
    sig = var(data);

    f = @(x) (1/sig/sqrt(2*pi))*exp(-0.5*(x-mu).^2/sig^2);
    xmin = min(data);
    xmax = max(data);

    deltax = abs(xmax-xmin)/50;
    x = xmin:deltax:xmax;
    y = f(x);

    plot(x, y);
end