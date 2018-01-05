function plotting(filename)

%{
Plotting the results based on input test filename
the filename should not contain the path, and the
result text file is assumed to be 'res_'+filename
in the same directory of this plotting.m script
%}

pc = importdata("test/"+filename);
ch = importdata("res_"+filename);
minx = min(ch(:,1));
maxx = max(ch(:,1));
miny = min(ch(:,2));
maxy = max(ch(:,2));
ch(end+1,:)=ch(1,:);
plot(pc(:,1), pc(:,2), 'b*', ch(:,1),ch(:,2),'r-O');
xlim([minx maxx]);
ylim([miny maxy]);
title("Results of "+filename);

end