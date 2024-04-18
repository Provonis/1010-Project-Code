function [centroidRowVec, centroidColVec, modImage] = FindAllTargetCentroids(testImage, targetRGB)
    modImage = testImage;
    for k = 1:6
        [centroidRow, centroidCol, modImage] = FindTargetCentroid(modImage,targetRGB);
        centroidRowVec(k) = centroidRow;
        centroidColVec(k) = centroidCol;
    end
end