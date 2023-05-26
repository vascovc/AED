
    X = tarefa;
    h = 8;
    for i = 1:1:40
        j = X(i,4);
        a = [X(i,1) X(i,2)];
        b = [j,j];
        hold on
        if X(i,4) ~= -1
            line(a,b,'LineWidth',3,'Color','k')
            plot(X(i,1),X(i,4),'ok','MarkerFaceColor','k')
            plot(X(i,2),X(i,4),'ok','MarkerFaceColor','k')
            t1 = (((a(1)+a(2))/2)-1); t2 = (j+(1/2));
            text(t1,t2,append('Task',int2str(i)))
        end
        if X(i,4) == -1
            line(a,[h,h],'LineWidth',3,'Color','r')
            plot(X(i,1),h,'or','MarkerFaceColor','r')
            plot(X(i,2),h,'or','MarkerFaceColor','r')
            t1 = (((a(1)+a(2))/2)-1); t2 = (h+(1/2));
            text(t1,t2,append('Task',int2str(i)),'Color','r')
            h = h+1;
        end
        
    end