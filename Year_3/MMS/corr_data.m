function f = corr_data(data1, data2)
    f = corrcoef(data1, data2);
    disp("Matrix " + f)
    plot(data1, data2, "x")
    xlabel("Data1")
    ylabel("Data2")
end 