function [s, state] = configSerialPort(serialPort)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
state=1;
s = serial(serialPort,'BaudRate', 9600, 'Parity','none', 'DataBits', 8, 'StopBits', 2, 'FlowControl','none'); %define com port
fopen(s);

recievedData='x';
while (recievedData~='a')
    recievedData=fread(s,1,'uchar');
end

if (recievedData=='a')
    disp('motor communication OK...')
end

fprintf(s, '%c', 'a');
fscanf(s,'%c');


end


