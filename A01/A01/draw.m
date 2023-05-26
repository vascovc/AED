
for i=1:40
    a = [X(i,1) X(i,2)]
    b = X(i,4)
    plot(a,b)
    hold on
    drawnow
end
hold off