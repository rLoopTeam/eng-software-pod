%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% filename: brakeactuator.m 
% author: dr. briefs
% last updated: 2017/8/10
%
% purpose: generates brake gap position based on brake actuator response dynamics
% 
% input: initial brake gap (mm), target brake gap (mm), time passed since t=0
% output: brake gap position (mm), settling time (s)
%
% notes: 
% response dynamics assumes...
% -no load conditions
% -constant max velocity of 6mm/s
% -constant acceleration of 4mm/s^2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [b,ts] = brakeactuator(b0,bset,t)
    deltab = bset - b0;
    bddotmax = 4.0;
    bdotmax = 6.0;
        
    % If required brakegap travel is greater than distance needed to accelerate and decelerate to/from max velocity:
    if abs(deltab) > bdotmax^2/bddotmax
        
        % Calculate theoretical time & distance required to accelerate to max speed
        deltab_accel = 0.5*bdotmax^2/bddotmax;
        deltat_accel = bdotmax/bddotmax;
        
        % Assume distance traveled during acceleration equals distance traveled during deceleration
        deltab_decel = deltab_accel;
        
        % Calculate required coast distance & time
        deltab_coast = abs(deltab) - deltab_accel - deltab_decel;
        deltat_coast = deltab_coast/bdotmax;
        
        % Calculate theoretical settling time
        ts = deltat_coast + 2*deltat_accel;
        
        % Calculate position given time
        if t <= deltat_accel % Calculate theoretical position if t is in acceleration phase
            b = b0 + 0.5*bddotmax*t^2;
            if deltab < 0
                b = b0 - 0.5*bddotmax*t^2;
            end
        elseif t > deltat_accel && t < deltat_accel + deltat_coast % Calculate theoretical position if t is in coasting phase
            b1 = b0 + 0.5*bddotmax*deltat_accel^2;
            b = b1 + bdotmax*(t - deltat_accel);
            if deltab < 0
                b1 = b0 - 0.5*bddotmax*deltat_accel^2;
                b = b1 - bdotmax*(t - deltat_accel);
            end
        elseif t > deltat_accel && t < ts % Calculate theoretical position if t is in deceleration phase
            b1 = b0 + 0.5*bddotmax*deltat_accel^2;
            b2 = b1 + bdotmax*deltat_coast;
            b = b2 + bdotmax*(t - deltat_accel - deltat_coast) - 0.5*bddotmax*(t - deltat_accel - deltat_coast)^2;
            if deltab < 0
                b1 = b0 - 0.5*bddotmax*deltat_accel^2;
                b2 = b1 - bdotmax*deltat_coast;
                b = b2 - bdotmax*(t - deltat_accel - deltat_coast) + 0.5*bddotmax*(t - deltat_accel - deltat_coast)^2;
            end
        else % If theoretical settling time exceeded, hold brakegap value at bset
            b = bset;
        end
            
    %% Travel distance too short to accelerate to max speed    
    else
        % Calculate theoretical distance required to accelerate to max speed
        deltab_accel = abs(deltab)/2;
        
        % Calculate new max speed
        bdotmax = sqrt(2*bddotmax*deltab_accel);
        
        % Calculate theoretical time required to accelerate to max speed
        deltat_accel = bdotmax/bddotmax;
        
        % Calculate theoretical settling time
        ts = 2*deltat_accel;
        
        % Calculate position given time
        if t <= deltat_accel % Calculate theoretical position if t is in acceleration phase
            b = b0 + 0.5*bddotmax*t^2;
            if deltab < 0
                b = b0 - 0.5*bddotmax*t^2;
            end
        elseif t > deltat_accel && t < ts % Calculate theoretical position if t is in deceleration phase
            b1 = b0 + 0.5*bddotmax*deltat_accel^2;
            b = b1 + bdotmax*(t - deltat_accel) - 0.5*bddotmax*(t - deltat_accel)^2;
            if deltab < 0
                b1 = b0 - 0.5*bddotmax*deltat_accel^2;
                b = b1 - bdotmax*(t - deltat_accel) + 0.5*bddotmax*(t - deltat_accel)^2;
            end
        else % If theoretical settling time exceeded, hold brake gap value at bset
            b = bset;
        end
    end
end


%% Discrete time calc based curve generator - don't use
% function [t,b] = brakeactuator(b0,bset,dt)
%     deltab = bset - b0;
%     bddotmax = 4.0;
%     bdotmax = 6.0;
% 
%     n = 1;
%     b = [b0];
%     bdot = [0];
%     t = [0];
%     
%     % If required brakegap travel is greater than time needed to accelerate and decelerate to/from max velocity:
%     if abs(deltab) > bdotmax^2/bddotmax
%         %% Generate acceleration phase
% %         while bdotmax^2/(2*bddotmax) - abs(b(n)) > 0.001
%         while abs(bdotmax - bdot(n)) > 0
% 
%             n = n + 1;
%             % Calculate speed
%             bdot(n) = bdot(n-1) + bddotmax*dt;
% 
%             if abs(bdot(n)) > abs(bdotmax)
%                 bdot(n) = bdotmax;
%             end
% 
%             % Calculate position
%             b(n) = b(n-1) + bdot(n-1)*dt + 0.5*bddotmax*dt^2;
%             if deltab < 0
%                 b(n) = b(n-1) - bdot(n-1)*dt - 0.5*bddotmax*dt^2;
%             end
% 
%             t(n) = t(n-1) + dt;
% 
%         end
%         
%         % Create timestamp
%         n1 = n;
%         b1 = b(n);
%         bdot1 = bdot(end);
%         t1 = t(end);
%         
%         %% Calculate required coast period
%         deltab_coast = abs(deltab) - 2*abs(b(end) - b(1));
% 
%         %% Generate coast phase
%         while deltab_coast - abs(b(n) - b1) > 0.001*deltab_coast
%             n = n + 1;
% 
%             % Calculate speed
%             bdot(n) = bdot(n-1);
% 
%             % Calculate position
%             b(n) = b(n-1) + bdot(n-1)*dt;
%             if deltab < 0
%                 b(n) = b(n-1) - bdot(n-1)*dt;
%             end
% 
%             t(n) = t(n-1) + dt;
% 
%         end
%         
%         % Create timestamp
%         b2 = b(end);
%         t2 = t(end);
%         
%         %% Generate deceleration phase
%         while t(n) - t2 < t1
%             n = n + 1;
% 
%             % Calculate speed
%             bdot(n) = bdot(n-1) - bddotmax*dt;
%             if bdot(n) < 0
%                 bdot(n) = 0;
%             end
% 
%             % Calculate position
%             b(n) = b(n-1) + bdot(n-1)*dt + 0.5*bddotmax*dt^2;
%             if deltab < 0
%                 b(n) = b(n-1) - bdot(n-1)*dt - 0.5*bddotmax*dt^2;
%             end
% 
%             t(n) = t(n-1) + dt;
%         end
%         b(end) = bset;	% Overwrite last brakegap value with bSet (to account for undershoot in code)
%         
%     %% Travel distance too short to accelerate to max speed    
%     else
%         %% Generate acceleration phase
%         % Compute new max speed based on required travel distance
%         bdotmax = sqrt(abs(deltab)*bddotmax);
%         %% Generate acceleration phase
%         while bdotmax - abs(bdot(n)) > 0.001* abs(bdotmax)
% 
%             n = n + 1;
%             % Calculate speed
%             bdot(n) = bdot(n-1) + bddotmax*dt;
% 
%             if abs(bdot(n)) > abs(bdotmax)
%                 bdot(n) = bdotmax;
%             end
%             
%             % Compute time-step
%             t(n) = t(n-1) + dt;
% 
%             % Calculate position
%             b(n) = b(n-1) + bdot(n-1)*dt + 0.5*bddotmax*dt^2;
%             if deltab < 0
%                 b(n) = b(n-1) - bdot(n-1)*dt - 0.5*bddotmax*dt^2;
%             end
%             % if half target distance is overshot, break acceleration phase
%             if abs(b(n) - b(1)) >= abs(deltab)/2
%                 break
%             end
%         end
%         t1= t(end);
%         %% Generate deceleration phase
%         while t(n) < 2*t1
%             n = n + 1;
% 
%             % Calculate speed
%             bdot(n) = bdot(n-1) - bddotmax*dt;
%             if bdot(n) < 0
%                 bdot(n) = 0;
%             end
% 
%             % Compute time-step
%             t(n) = t(n-1) + dt;
% 
%             % Calculate position
%             b(n) = b(n-1) + bdot(n-1)*dt + 0.5*bddotmax*dt^2;
%             if deltab < 0
%                 b(n) = b(n-1) - bdot(n-1)*dt - 0.5*bddotmax*dt^2;
%             end
%             % if target distance is overshot, break deceleration phase
%             if abs(b(n) - b(1)) >= abs(deltab)
%                 break
%             end
%         end
%         b(end) = bset;	% Overwrite last brakegap value with bSet (to account for undershoot in code)        
%     end
% end
