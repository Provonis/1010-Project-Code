function [centroidRow, centroidCol, modImage] = FindTargetCentroid(testImage,targetRGB)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    redLayer = testImage(:,:,1);
    greenLayer = testImage(:,:,2);
    blueLayer = testImage(:,:,3);
    
    logArray = redLayer == targetRGB(1) & greenLayer == targetRGB(2) & blueLayer == targetRGB(3);
    
    [matchRows, matchCols] = find(logArray == 1);
    
    firstMatchRow = matchRows(1);
    firstMatchCol = matchCols(1);
    
    [rows,cols,colors] = size(testImage);
    
    for c = firstMatchCol:cols
        if logArray(firstMatchRow,c+1) == 0;
            break
        end
    end
    lastMatchCol = c;
    for r = firstMatchRow:rows
        if logArray(r+1, firstMatchCol) == 0;
            break
        end
    end
    
    lastMatchRow = r;
    centroidRow = (firstMatchRow + lastMatchRow)/2;
    centroidCol = (firstMatchCol + lastMatchCol)/2;
    modImage = testImage;
    modImage(firstMatchRow:lastMatchRow, firstMatchCol:lastMatchCol,:) = 0;
end