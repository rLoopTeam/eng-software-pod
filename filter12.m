close all
clear all

Fs = 5000;
fc = 320;
N = 40;

F1 = 200;
F2 = 100;
F3 = 500;
F4 = 150;
F5 = 1000;
F6 = 2000;
F7 = 2100;
F8 = 2200;

t_n = 0:1/Fs:1;

s = 5*sin(2*pi*F1*t_n) + 3*sin(2*pi*F2*t_n) + sin(2*pi*F3*t_n) + 2*sin(2*pi*F4*t_n) + sin(2*pi*F5*t_n) + sin(2*pi*F6*t_n) + sin(2*pi*F7*t_n) + sin(2*pi*F8*t_n);

b = fir1(N, fc/(Fs/2));
[h, w] = freqz(b, 1, 256, Fs);

figure
plot(w, abs(h)), grid

figure
stem(abs(fft(s)))

y = filter(b, 1, s);
figure
stem(abs(fft(y)));




