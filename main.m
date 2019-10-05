X = 100;
Y = 100;
MAX_DEVIATION = 10^-6;
up_temp = 0;
down_temp = 0;
left_temp = 100;
right_temp = 0;
temps = [linspace(up_temp,up_temp,X);repmat(linspace(left_temp,right_temp,X),Y-2,1);linspace(down_temp,down_temp,X)];
counter = 0;
while true
    [temps, deviation] = temp_interation(temps);
    counter = counter + 1;
    if deviation < MAX_DEVIATION
        break
    end
end
temps
counter
