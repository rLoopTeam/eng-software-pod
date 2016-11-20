%we need dsp for this
pkg load signal;

%load the CSV file, start at 1,1
%input_csv = csvread("Flig_tellog_2016-11-18_18_18.csv", 1, 1);

%load all our CSV files
csv_dir = dir("*.csv");

%setup the channel indexes into the csv file
ch_idx__accel_x = 57;
ch_idx__accel_y = 60;
ch_idx__accel_z = 63;

%setup the laser indexes
ch_idx_laser_l_aft_height = 39;
ch_idx_laser_r_aft_height = 42;
ch_idx_laser_aft_yaw = 45;

%apply a little random offset to bring one of the
%lasers into graphing distance
laser_offst_mm = -3;

%loop through all the csv diles
for csv_count = length(csv_dir):-1:1;

  %read the file
  input_csv = csvread(csv_dir(csv_count).name, 1, 1);
  
  %plot the laser data
  subplot(2,2,1);
  plot(input_csv(:, ch_idx_laser_l_aft_height) - laser_offst_mm, 'r', 'DisplayName','L AFT Height');
  hold on;
  plot(input_csv(:, ch_idx_laser_r_aft_height), 'g', 'DisplayName','R AFT Height');
  hold off;
  title("Height");
  xlabel('Samples');
  ylabel('Height (mm)');
  %legend('show');


  subplot(2,2,2);
  plot(input_csv(:, ch_idx_laser_aft_yaw), 'b', 'DisplayName','AFT Yaw');
  title("Yaw");
  xlabel('Samples');
  ylabel('Distance (mm)');
  %legend('show');


  %plot the accel data
  subplot(2,2,3);
  plot(input_csv(:, ch_idx__accel_x), 'r');
  hold on;
  plot(input_csv(:, ch_idx__accel_y), 'g');
  hold off;
  title("Acceleration");
  xlabel('Samples');
  ylabel('G-Force (uncalibrated)');
  %legend('show');

  subplot(2,2,4);
  plot(input_csv(:, ch_idx__accel_z), 'b');
  title("Acceleration");
  xlabel('Samples');
  ylabel('G-Force (uncalibrated)');
  %legend('show');
  
  %make some png files.
  print('-dpng', strcat('png/',csv_dir(csv_count).name,".png"));
  
end;





