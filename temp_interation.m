function [temps, deviation] = temp_interation(temps)
    [max_x, max_y] = size(temps);
    tmp = temps;
    for x=2:max_x-1
        for y=2:max_y-1
            temps(x,y)=(temps(x-1,y)+temps(x+1,y)+temps(x,y-1)+temps(x,y+1))./4;
        end
    end
    deviation = max(max(abs((tmp(2:max_x,2:max_y)-temps(2:max_x,2:max_y))./tmp(2:max_x,2:max_y))));
end