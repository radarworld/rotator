clc;
clear all;
serialPort='COM5';

if(~exist('serialState', 'var'))
    [s,serialState] = configSerialPort(serialPort);
end



msg=sendMot(s, 'R')

msg=sendMot(s, 'L')

msg=sendMot(s, 'H')

fclose(s)
delete(s)
