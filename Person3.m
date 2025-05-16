clc
clear all
close all

%uploading the first data with the name normal
load('data03.dat');
normal = data03;

%uploading the second data with the name bradycardia
load('data17.dat');
bradycardia = data17;

%uploading the third data with the name tachycardia
load('data29.dat');
tachycardia = data29;

t = 1/8000:1/8000:15;

%combining the data
person3 = vertcat(normal, bradycardia, tachycardia);
plot(t,person3);

%tabulation of data with second values
veriTable = table(t',person3,'VariableNames',{'Time','Voltage'});

%saving the merged data as a txt file
disp(veriTable);

writetable(veriTable, 'person3.txt','Delimiter','\t');

%saving the merged data as a dat file
disp(veriTable);

writetable(veriTable, 'person3.dat','Delimiter','\t');