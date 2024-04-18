function [key] = kbhit(cmd)
% ** WITH THE COMMAND WINDOW ACTIVE **
% Returns the lowercase letter of a pressed letter key
% Returns char(0):
%   - until a key is pressed
%   - between key presses
%   - when a key other than a letter key is pressed
%
% kbhit('init')        : initialize listening
% key = kbhit          : last character typed
% kbhit('stop')        : turn off listening
%
% Created by Amanda Ng 3 March 2011
%   https://www.mathworks.com/matlabcentral/answers/291975-any-function-like-kbhit
%   https://www.mathworks.com/matlabcentral/answers/uploaded_files/249352/kbhit.m
% Modified by DJM 19 November 2021

    narginchk(0, 1)
    
    global KBHIT_Data
    global KBHIT_h_cw
    global KBHIT_h_cw_cbp
    
    key = char(0);
    %key = [];
    
    if nargin == 0
        if isempty(KBHIT_h_cw_cbp)
            error('kbhit has not been initialised.');
        else
            event = KBHIT_Data;
            if ~isempty(event)
                temp = get(event, 'KeyChar'); % changed from KeyCode to KeyChar
                if temp >= 97 & temp <= 122
                    key = char(temp);
                else
                    key = char(0);
                end
                KBHIT_Data = []; % added so can detect the same key when pressed again
            end
        end
    elseif nargin == 1
        switch lower(cmd)
            case 'init'
                try
                    mde = com.mathworks.mde.desk.MLDesktop.getInstance;
                    KBHIT_h_cw = mde.getClient('Command Window');
                    xCmdWndView = KBHIT_h_cw.getComponent(0).getViewport.getComponent(0);
                    KBHIT_h_cw_cbp = handle(xCmdWndView,'CallbackProperties');
                    javastr = ['global KBHIT_Data; ' ...
                        'KBHIT_Data = get(gcbo, ''KeyPressedCallbackData''); '...
                        ];
                    set(KBHIT_h_cw_cbp, 'KeyPressedCallback', javastr);
                    KBHIT_Data = [];
                    key = 1;
                catch ME
                    key = 0;
                end
            case 'stop'
                set(KBHIT_h_cw_cbp, 'KeyPressedCallback', []);
                clear global KBHIT_h_cw KBHIT_h_cw_cbp KBHIT_ctrl_code
            otherwise
                error('Unrecognised parameter');
        end
    end
end      