%%%%%%%%%%%%%%%%%%%%%
% James Utton
% u1468024
% ME EN 1010 Lab Section 004
% Demo 3
% 04/09/2024
%%%%%%%%%%%%%%%%%%%%%
clear, clc, close all
%% Image Procesing
imageArray = imread("S24_QP_A2.bmp");
disp("Click on whacked mole to get color information");
keyRGB = ColorPicker(imageArray)
targetRGB = keyRGB - 1
[centroidRowVec, centroidColVec, modImage] = FindAllTargetCentroids(imageArray, targetRGB);
figure
image(modImage)
hold on
plot(centroidColVec, centroidRowVec,'wx');
drawnow();
stripeNum = centroidRowVec/10
xTargetM = (450+centroidColVec)/1000


%%
target = 0:5;
% serial communication setup
RomeoCOM = serialport('/dev/cu.usbmodem1201',9600);
endCheck = "done";
dataCheck = "ready for data";

% key press detection setup
kbhit('init');
key = char(0);
prevKey = key;

while(1)
    % key press detection
    prevKey = key;
    key = kbhit;
    pause(1/6000) % seconds
    if key == 'q'
        disp('MATLAB aborting');
        break
    elseif key ~= char(0)
        disp('sending letter to Arduino')
        writeline(RomeoCOM,key)
     end

    % serial communication
    if RomeoCOM.NumBytesAvailable > 0   
        message = readline(RomeoCOM);
        message = erase(message,sprintf('\r'));
        % if Romeo sends special done message, break out of scanning loop
        if strcmp(message, endCheck) == 1
            break
        elseif strcmp(message, dataCheck) == 1
            % send data to romeo and recieve messages back
            disp("sending data to romeo");
            [sortStripeNum, sortIdx] = sort(stripeNum);
            sortXTargetM = xTargetM(sortIdx);
            for target = 2:6;
                % try sending an integer value as a string to romeo
                out1 = sprintf('%d', sortStripeNum(target));
                writeline(RomeoCOM, out1)
                out2 = sprintf('%.3f', sortXTargetM(target));
                writeline(RomeoCOM, out2);
                message = readline(RomeoCOM);
                message = erase(message,sprintf('\r'));
                disp(message)
            end
            out1 = sprintf('%d', sortStripeNum(1));
            writeline(RomeoCOM, out1);
            out2 = sprintf('%.3f', sortXTargetM(1));
            writeline(RomeoCOM, out2);
            message = readline(RomeoCOM);
            message = erase(message, sprintf('\r'));
            disp(message);
        else
            disp(message)
        end

    end
end
clear RomeoCOM
kbhit('stop');


