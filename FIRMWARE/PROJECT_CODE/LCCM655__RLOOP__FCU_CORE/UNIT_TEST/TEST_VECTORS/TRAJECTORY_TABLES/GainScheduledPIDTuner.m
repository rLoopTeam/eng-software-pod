%% Designing a Family of PID Controllers for Multiple Operating Points
% This example shows how to design an array of PID controllers for a nonlinear
% plant in Simulink that operates over a wide range of operating points. 

%%
% Run brakingTrajectory.m prior to running this code

%%
% Import plant model
mdl = 'BrakingSystemPlant';
%mdl = 'scdcstrctrlplant';
open_system(mdl)

%%
% Obtain default operating point
op = operspec(mdl); 
% Set the value of output concentration C to be known
op.Outputs.Known = true;                
% Specify operating regions 
xdotset_range = xdotf:10:xdot2;
% xdotset_range = xdotf:10:xdot3;
%xdotset_range = xdot0:-10:xdotf;
% Initialize an array of state space systems
Plants = rss(1,1,1,8);
for ct = 1:length(xdotset_range)
    % Compute equilibrium operating point corresponding to the value of xdotset_range
    op.Outputs.y = xdotset_range(ct);
    opoint = findop(mdl,op,findopOptions('DisplayReport','off')); 
    % Linearize plant at this operating point
    Plants(:,:,ct) = linearize(mdl, opoint); 
end

%%
% Since the plant is nonlinear, we expect different characteristics
% among the linear models.
isstable(Plants,'elem')'

%% Designing PID Controllers for the Plant Models
% To design multiple PID controllers in batch, we can use the |pidtune|
% command. The following command will generate an array of PID controllers
% in parallel form. The desired open loop crossover frequency is at 1
% rad/sec and the phase margin is the default value of 60 degrees.

% Design controllers
Controllers = pidtune(Plants,'pidf',pidtuneOptions('Crossover',1));
% Display controller for xdotset_range=4
Controllers(:,:,4)

%%
% Plot the closed loop responses for step set-point tracking as below:

% Construct closed-loop systems
clsys = feedback(Plants*Controllers,1);
% Plot closed-loop responses
figure;
hold on
for ct = 1:length(xdotset_range)
    % Select a system from the LTI array
    sys = clsys(:,:,ct);
    sys.Name = ['xdotset_range=',num2str(xdotset_range(ct))];
    sys.InputName = 'Reference';
    % Plot step response
    stepplot(sys,20);
end
legend('show','location','southeast')

%%
% All the closed loops are stable but the overshoots of the loops with
% unstable plants (xdotset_range=4, 5, 6, and 7) are too large.  To improve the results, 
% increase the target open loop bandwidth to 10 rad/sec.

% Design controllers for unstable plant models
Controllers = pidtune(Plants,'pidf',10);
% Display controller for xdotset_range=4
Controllers(:,:,4)

%%
% Plot the closed-loop step responses for the new controllers. 

% Construct closed-loop systems
clsys = feedback(Plants*Controllers,1);
% Plot closed-loop responses
figure;
hold on
for ct = 1:length(xdotset_range)
    % Select a system from the LTI array
    sys = clsys(:,:,ct);
    set(sys,'Name',['xdotset_range=',num2str(xdotset_range(ct))],'InputName','Reference');
    % Plot step response
    stepplot(sys,20);
end
legend('show','location','southeast')
%%
% All the closed loop responses are satisfactory now. For comparison,
% examine the response when you use the same controller at all operating
% points.  Create another set of closed-loop systems, where each one uses
% the xdotset_range = 2 controller.
clsys_flat = feedback(Plants*Controllers(:,:,1),1);

figure;
stepplot(clsys,clsys_flat,20)
legend('xdotset_range-dependent Controllers','Single Controller')
%%
% The array of PID controllers designed separately for each concentration
% gives considerably better performance than a single controller.
% 
% However, the closed-loop responses shown above are computed based on
% linear approximations of the full nonlinear system.  To validate the
% design, implement the scheduling mechanism in your model using the PID
% Controller block.
%%
% Close the model.
bdclose(mdl);
displayEndOfDemoMessage(mfilename)

%%
% Open Gain-scheduled PID Controller Simulink Model
pidmdl = 'GainScheduledPIDBrakingSystem';
open_system(pidmdl)
