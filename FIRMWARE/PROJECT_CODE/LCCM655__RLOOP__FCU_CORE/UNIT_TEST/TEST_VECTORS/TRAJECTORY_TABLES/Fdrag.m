classdef Fdrag
    ...
    methods(Static)
        
        %% Aero drag
        % Input: velocity (m/s), brakegap (mm), hover height (mm)
        % Output: Drag force (N)
        function F = aero(v,rho)
            %%%% Aero Drag parameters %%%%
            Cd = 1.1849;        % Drag coeff
            Ap = 1.14;          % Projectet drag area

            %%%% Compute aerodrag %%%%
            F =  rho * Cd * Ap * v^2 / 2;
            
            if F < 0
                F = 0;
            end
        end
        
        % Input: velocity (m/s), brakegap (mm), hover height (mm)
        % Output: Total brake drag force (N)
        function F = brake(v,bg)
            F = (5632 * exp(-202*bg*10^-3) * (-exp(-0.3*v) + 1) * (1.5*exp(-0.02*v) + 1) );
            
            if F < 0
                F = 0;
            end
        end
        
        %% Hover drag for hover engines rotating at 2000 rpm
        % Input: velocity (m/s), brakegap (mm), hover height (m)
        % Output: Total brake drag force (N)
        function F = hover(v,z)

            %%%% Hover Drag parameters %%%%
            N_he = 8;           % No. of hover engines

            F = 0.5 * N_he * (z*(-14166.667)+235) * (-exp(-0.16*v) + 1) * (1.6*exp(-0.02*v) + 1);
%             F = 0.5 * N_he * (z*10^(-3)*(-14166.667)+235) * (-exp(-0.16*v) + 1) * (1.6*exp(-0.02*v) + 1);
        %     F = 0.25*N_he*Fhoverlift(v,z,0);     % Total hover drag estimated as 1/4th hover lift at 0 rpm

            if F < 0
                F = 0;
            end

        %    F = 150 * (-exp(-0.16*v) + 1) * (1.6*exp(-0.02*v) + 1);
        %    F = 0;

        end
        
        %% Ski drag at 16mm hover height
        % Input: velocity (m/s), hover height (m) (unused)
        % Output: Total ski drag force (N)
        function F = ski(v,z_nom)
            F = 204.983 * exp(-0.004*v);
            if F <= 0
                F = 0;
            end
        end
        
    end
    
end