

N=200;
radius = 2.7*10^(-2);
CandelasPerMetreSquared = zeros(1,N);
for k=1:1:N

    milicandelas = 200 + k;

    Candelas = milicandelas*10^(-3);

    Area = pi*(radius^2);

    CandelasPerMetreSquared(1,k) = Candelas/Area;

end
candelaRange = N:1:400-1;
plot(candelaRange, CandelasPerMetreSquared)
ylabel('Intensity of Light Over an Area (Cd/m^2)');
xlabel('NeoPixel Blue Light Intensity (mCd)');
title('NeoPixel Blue Light Distribution for a range of Predicted Intensities');