% Input: velocity (m/s), brakegap (mm)
% Output: Brake lift force for one brakepad (N)
function F = Fbrakelift(v,bg)
    F = 3265.1 * exp(-209.4*bg*10^-3) * log(v + 1) - 2636.7*exp(-207*bg*10^-3) * (v + 0.6) * exp(-0.16*v);
end