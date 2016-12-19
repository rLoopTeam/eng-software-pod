
#setup
#set lvhd087_tbpath "$tbpath${ps}lvhd087_sim_hyperloop_0${ps}lvhd087_sim_hyperloop_0" 

eval add wave -noupdate -divider {"lvhd087_sim_hyperloop - TOP"}
eval add wave -noupdate $binopt $lvhd087_tbpath${ps}hloop_laser_o
#eval add wave -noupdate $binopt $lvhd087_tbpath${ps}hloop_clk_i

eval add wave -noupdate -divider {"TIMEBASE"}
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_time_base_ns
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_time_base_squared_ns
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_current_accel_x1000g
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_accel_time_mult
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_accel_time_mult_05
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_ut
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_displacement
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_current_veloc
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_max_veloc


eval add wave -noupdate -divider {"CONTROL"}
eval add wave -noupdate $binopt $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_control_run_on
eval add wave -noupdate $binopt $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_sm_state
eval add wave -noupdate $binopt $lvhd087_tbpath${ps}USER_LOGIC_I${ps}s_coast_active

eval add wave -noupdate -divider {"SLAVE REGS"}
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}slv_reg1;
eval add wave -noupdate -radix unsigned $lvhd087_tbpath${ps}USER_LOGIC_I${ps}slv_reg2;