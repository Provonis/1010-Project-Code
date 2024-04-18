function [RGB] = ColorPicker(imageArray)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

    % Display the image
    image(imageArray);

    % Select pixel
    [x, y] = ginput(1);

    % Round x and y values
    x = round(x);
    y = round(y);
    
    % index out of image array vector
    RGB = imageArray(y,x,:);
end