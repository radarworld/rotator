function [ serialData ] = getDataMotor(s,bytesToReceive)
%getDataXMC Send command to XMC and get the answer

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% message format:[CMD PARAM DATA]                      %
% CMD:    1=get, 2=set                                 %
% PARAM:  1=IF1Q                                       %
% LENGTH: 5=number of expected bytes in the answer     %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%97: home
%98: step clockwise
%99: step counter clockwise

command=[97];  %read IFQ1 channel

fwrite(s, command,'sync')  %send 
pause(0.1)

%while(s.BytesAvailable ~= bytesToReceive)  %wait for uC response
%end
while(s.BytesAvailable)
end

X = [num2str(s.BytesAvailable),' bytes received from uC'];
disp(X) %Dispaly the number of bytes in buffer.

serialData =fread(s,s.BytesAvailable);    %read the data from buffer
%X = [num2str(s.BytesAvailable),' bytes remained in buffer after read.'];
%disp(X) %Dispaly the number of bytes in buffer.

pause(0.01)


end

