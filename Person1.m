clc
clear all
close all

%uploading the first data with the name normal
load('data06.dat');
normal = data06;

%uploading the second data with the name bradycardia
load('data18.dat');
bradycardia = data18;

%uploading the third data with the name tachycardia
load('data21.dat');
tachycardia = data21;

t = 1/8000:1/8000:15;

%combining the data
person1 = vertcat(normal, bradycardia, tachycardia);
plot(t,person1);

%tabulation of data with second values
veriTable = table(t',person1,'VariableNames',{'Time','Voltage'});

%saving the merged data as a txt file
disp(veriTable);

writetable(veriTable, 'person1.txt','Delimiter','\t');

%saving the merged data as a dat file
disp(veriTable);

writetable(veriTable, 'person1.dat','Delimiter','\t');