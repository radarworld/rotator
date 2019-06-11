function [outputArg] = sendMot(s,command)
%sendMot move motor one step clockwise
%   Detailed explanation goes here

%send serial command to arduino
fprintf(s, command);
outputArg = fread(s, 1,'uint8');

end

