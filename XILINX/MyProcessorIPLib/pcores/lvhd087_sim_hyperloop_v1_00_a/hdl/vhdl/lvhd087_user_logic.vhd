
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

library lvhd022_xilinx_proc_common_v3_00_a;
use lvhd022_xilinx_proc_common_v3_00_a.proc_common_pkg.all;

library lvhd087_sim_hyperloop_v1_00_a;
use lvhd087_sim_hyperloop_v1_00_a.all;
use lvhd087_sim_hyperloop_v1_00_a.lvhd087_pkg.all;

entity user_logic is
	generic
	(
	
		G_HYPERLOOP_NUM_LASERS : integer := 1;
		C_SPLB_CLK_FREQ_HZ : integer := 100_000_000;

		--The size of the timbase generator in bits
		--This value drives many other systems and reducing it by even a few bits will
		--have a massive effect on the final FPGA size.
		--2^64ns = Long Time
		--2^32ns = 4.2 seconds
		--2^40ns = 18 minutes and could be long enough to simulate auxprop extraction from the tube.
		G_HYPERLOOP_TIMEBASE_SIZE : integer := 40;
		
		-- Bus protocol parameters, do not add to or delete
		C_SLV_DWIDTH : integer := 32;
		C_NUM_REG : integer := 16;
		C_FAMILY : string := "virtex6"
	);
	port
	(
		--! the laser output
		hloop_laser_o : out std_logic_vector((G_HYPERLOOP_NUM_LASERS - 1) downto 0);

		--! Start / stop debug out
		hloop_start_o : out std_logic;
		
		--! Timing Clock
		hloop_clk_i : in std_logic;
		
		-- Bus protocol ports, do not add to or delete
		Bus2IP_Clk : in std_logic;
		Bus2IP_Reset : in std_logic;
		Bus2IP_Data: in std_logic_vector(0 to C_SLV_DWIDTH-1);
		Bus2IP_BE : in std_logic_vector(0 to C_SLV_DWIDTH/8-1);
		Bus2IP_RdCE: in std_logic_vector(0 to C_NUM_REG-1);
		Bus2IP_WrCE: in std_logic_vector(0 to C_NUM_REG-1);
		IP2Bus_Data: out std_logic_vector(0 to C_SLV_DWIDTH-1);
		IP2Bus_RdAck : out std_logic;
		IP2Bus_WrAck : out std_logic;
		IP2Bus_Error : out std_logic
	);

	attribute MAX_FANOUT : string;
	attribute SIGIS : string;

	attribute SIGIS of Bus2IP_Clk	: signal is "CLK";
	attribute SIGIS of Bus2IP_Reset : signal is "RST";

end entity;

------------------------------------------------------------------------------
-- Architecture section
------------------------------------------------------------------------------

architecture arch_user_logic of user_logic is

 
	------------------------------------------
	-- Signals for user logic slave model s/w accessible register example
	------------------------------------------
	signal slv_reg0 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg1 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg2 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg3 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg4 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg5 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg6 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg7 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg8 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg9 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg10 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg11 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg12 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg13 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg14 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg15 : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_reg_write_sel : std_logic_vector(0 to 15);
	signal slv_reg_read_sel : std_logic_vector(0 to 15);
	signal slv_ip2bus_data : std_logic_vector(0 to C_SLV_DWIDTH-1);
	signal slv_read_ack : std_logic;
	signal slv_write_ack : std_logic;

	--The timer in 10ns increments but at 1ns time.
	signal s_time_base_ns : std_logic_vector((G_HYPERLOOP_TIMEBASE_SIZE - 1) downto 0);
	
	--We need to compute t^2 so this will be done here.
	signal s_time_base_squared_ns : std_logic_vector(((G_HYPERLOOP_TIMEBASE_SIZE * 2) - 1) downto 0);
	
	--The current acceleration
	signal s_current_accel_x1000g : std_logic_vector(((G_HYPERLOOP_TIMEBASE_SIZE * 2) - 1) downto 0);
	
	--The multiplication of at^2
	signal s_accel_time_mult : std_logic_vector(((G_HYPERLOOP_TIMEBASE_SIZE * 4) - 1) downto 0);
	
	--velocity based on v0+at (only good for accel phase to get our coast)
	signal s_current_veloc : std_logic_vector(((G_HYPERLOOP_TIMEBASE_SIZE * 3) - 1) downto 0);
	
	--user programmable max veloc.
	signal s_max_veloc : std_logic_vector(((G_HYPERLOOP_TIMEBASE_SIZE * 3) - 1) downto 0);
	
	--1/2at^2
	signal s_accel_time_mult_05 : std_logic_vector(((G_HYPERLOOP_TIMEBASE_SIZE * 4) - 1) downto 0);
	
	--U = initial veloc - meters per second * 1000
	signal s_initial_ms : std_logic_vector((G_HYPERLOOP_TIMEBASE_SIZE - 1) downto 0);
	
	-- u * t
	signal s_ut : std_logic_vector(((G_HYPERLOOP_TIMEBASE_SIZE * 2) - 1) downto 0);
	
	--the total displacement based on s = ut + 1/2at^2
	signal s_displacement : std_logic_vector(((G_HYPERLOOP_TIMEBASE_SIZE * 2) - 1) downto 0);
	
	
	--basic state
	type CTL_STATE_TYPE is 
	(
		--! Idle state waiting for a run
		ST_IDLE,
		
		ST_ACCEL,
		
		ST_COAST,
		
		ST_DECEL,
		
		ST_STOP
		
	);
	signal s_sm_state : CTL_STATE_TYPE;
	
	--do we need to start coasting.
	signal s_coast_active : std_logic;
	
	--do we need to decel?
	signal s_decel_active : std_logic;
	
	signal s_laser_rise : std_logic;
	signal s_laser_fall : std_logic;
	
	--set from the host to start the run
	signal s_control_run_on : std_logic;
	
begin

 --USER logic implementation added here
 slv_reg_write_sel <= Bus2IP_WrCE(0 to 15);
 slv_reg_read_sel <= Bus2IP_RdCE(0 to 15);
 slv_write_ack	<= Bus2IP_WrCE(0) or Bus2IP_WrCE(1) or Bus2IP_WrCE(2) or Bus2IP_WrCE(3) or Bus2IP_WrCE(4) or Bus2IP_WrCE(5) or Bus2IP_WrCE(6) or Bus2IP_WrCE(7) or Bus2IP_WrCE(8) or Bus2IP_WrCE(9) or Bus2IP_WrCE(10) or Bus2IP_WrCE(11) or Bus2IP_WrCE(12) or Bus2IP_WrCE(13) or Bus2IP_WrCE(14) or Bus2IP_WrCE(15);
 slv_read_ack	<= Bus2IP_RdCE(0) or Bus2IP_RdCE(1) or Bus2IP_RdCE(2) or Bus2IP_RdCE(3) or Bus2IP_RdCE(4) or Bus2IP_RdCE(5) or Bus2IP_RdCE(6) or Bus2IP_RdCE(7) or Bus2IP_RdCE(8) or Bus2IP_RdCE(9) or Bus2IP_RdCE(10) or Bus2IP_RdCE(11) or Bus2IP_RdCE(12) or Bus2IP_RdCE(13) or Bus2IP_RdCE(14) or Bus2IP_RdCE(15);

 -- implement slave model software accessible register(s)
 SLAVE_REG_WRITE_PROC : process( Bus2IP_Clk ) is
 begin

	if Bus2IP_Clk'event and Bus2IP_Clk = '1' then
	if Bus2IP_Reset = '1' then
		slv_reg0 <= (others => '0');
		slv_reg1 <= (others => '0');
		slv_reg2 <= (others => '0');
		slv_reg3 <= (others => '0');
		slv_reg4 <= (others => '0');
		slv_reg5 <= (others => '0');
		slv_reg6 <= (others => '0');
		slv_reg7 <= (others => '0');
		slv_reg8 <= (others => '0');
		slv_reg9 <= (others => '0');
		slv_reg10 <= (others => '0');
		slv_reg11 <= (others => '0');
		slv_reg12 <= (others => '0');
		slv_reg13 <= (others => '0');
		slv_reg14 <= (others => '0');
		slv_reg15 <= (others => '0');
		
		--reset the laser nibbles here
		-- for j in 0 to G_HYPERLOOP_NUM_LASERS - 1 loop
			-- for k in 0 to 3 - 1 loop
				-- s_laser_nibbles(j)(k) <= (others => '0');
			-- end loop;
		-- end loop;
		
	else
		case slv_reg_write_sel is
		when "1000000000000000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg0(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0100000000000000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg1(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0010000000000000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg2(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0001000000000000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg3(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000100000000000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg4(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000010000000000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg5(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000001000000000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg6(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000000100000000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg7(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000000010000000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg8(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000000001000000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg9(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000000000100000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg10(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000000000010000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg11(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000000000001000" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg12(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000000000000100" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg13(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000000000000010" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg14(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when "0000000000000001" =>
			for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
			if ( Bus2IP_BE(byte_index) = '1' ) then
				slv_reg15(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
			end if;
			end loop;
		when others => null;
		end case;
	end if;
	end if;

 end process SLAVE_REG_WRITE_PROC;

 -- implement slave model software accessible register(s) read mux
 SLAVE_REG_READ_PROC : process( slv_reg_read_sel, slv_reg0, slv_reg1, slv_reg2, slv_reg3, slv_reg4, slv_reg5, slv_reg6, slv_reg7, slv_reg8, slv_reg9, slv_reg10, slv_reg11, slv_reg12, slv_reg13, slv_reg14, slv_reg15 ) is
 begin

	case slv_reg_read_sel is
		when "1000000000000000" => slv_ip2bus_data <= slv_reg0;
		when "0100000000000000" => slv_ip2bus_data <= slv_reg1;
		when "0010000000000000" => slv_ip2bus_data <= slv_reg2;
		when "0001000000000000" => slv_ip2bus_data <= slv_reg3;
		when "0000100000000000" => slv_ip2bus_data <= slv_reg4;
		when "0000010000000000" => slv_ip2bus_data <= slv_reg5;
		when "0000001000000000" => slv_ip2bus_data <= slv_reg6;
		when "0000000100000000" => slv_ip2bus_data <= slv_reg7;
		when "0000000010000000" => slv_ip2bus_data <= slv_reg8;
		when "0000000001000000" => slv_ip2bus_data <= slv_reg9;
		when "0000000000100000" => slv_ip2bus_data <= slv_reg10;
		when "0000000000010000" => slv_ip2bus_data <= slv_reg11;
		when "0000000000001000" => slv_ip2bus_data <= slv_reg12;
		when "0000000000000100" => slv_ip2bus_data <= slv_reg13;
		when "0000000000000010" => slv_ip2bus_data <= slv_reg14;
		when "0000000000000001" => slv_ip2bus_data <= slv_reg15;
	when others => slv_ip2bus_data <= (others => '0');
	end case;

 end process SLAVE_REG_READ_PROC;

	------------------------------------------
	-- Example code to drive IP to Bus signals
	------------------------------------------
	IP2Bus_Data <= slv_ip2bus_data when slv_read_ack = '1' else (others => '0');

	IP2Bus_WrAck <= slv_write_ack;
	IP2Bus_RdAck <= slv_read_ack;
	IP2Bus_Error <= '0';

	--host reg settings
	s_control_run_on <= slv_reg0(31);
	
	hloop_start_o <= s_control_run_on;
	
	--Displacement:
	--S = ut + 1/2at^2
	
	
	--Process to keep time increments going.
	--At 50MHZ, each time slice is 20ns.
	P_TIMEBASE : process(hloop_clk_i, Bus2IP_Reset, s_control_run_on)
	begin
		if Bus2IP_Reset = '1' or s_control_run_on = '0' then
			--clear the timer.
			s_time_base_ns <= (others => '0');
			
			--clear t^2
			s_time_base_squared_ns <= (others => '0');
			
			--at^2 sum
			s_accel_time_mult <= (others => '0');
			
			--initial veloc = 0 for now.
			s_initial_ms <= std_logic_vector(to_unsigned(0, G_HYPERLOOP_TIMEBASE_SIZE));
			
			--u * t
			s_ut <= (others => '0');
			
		elsif rising_edge(hloop_clk_i) then
			--out system clock is 20ns, but increment the timer by 10ns as we want
			--the timer in ns resolution
			s_time_base_ns <= s_time_base_ns + 20;
			
			--let VHDL sort out the multiplier
			s_time_base_squared_ns <= s_time_base_ns * s_time_base_ns;
			
			--compute at^2
			s_accel_time_mult <= s_time_base_squared_ns * s_current_accel_x1000g;
			
			--compute u*t
			s_ut <= s_initial_ms * s_time_base_ns;
			
		end if;	
	
	end process;
	
	--do the actual computation
	P_COMPUTE : process(hloop_clk_i, Bus2IP_Reset)
	begin
		if Bus2IP_Reset = '1' then
		
			--displacement is zero for starters.
			s_displacement <= (others => '0');
			s_current_accel_x1000g <= (others => '0');
			s_current_veloc <= (others => '0');
			s_max_veloc <= (others => '0');
			
			--initial states
			s_sm_state <= ST_IDLE;
			
		elsif rising_edge(hloop_clk_i) then
		
		
			case s_sm_state is
				
					when ST_IDLE =>
						
						--in idle state we are allowed to get updates from the app
						--Set our acceleration
						--2G = 2 * 9.8 = 19.6
						--mult x 1000 = 19600
						s_current_accel_x1000g(31 downto 0) <= slv_reg1;
						--std_logic_vector(to_unsigned(19600, 128));
						
						--assign shift the max velocity from the user.
						--15AA2199AFC600 = 6098035800000000
						--Approx 61x10^14
						s_max_veloc <= slv_reg2 * std_logic_vector(decimal_string_to_unsigned("100000000000", s_max_veloc'length - slv_reg2'length));
						
						--wait for the user to start the trigger
						if s_control_run_on = '1' then
							s_sm_state <= ST_ACCEL;
						else
							--stay in state
							s_sm_state <= ST_IDLE;
						end if;
						
					when ST_ACCEL =>

						--recompute
						s_displacement <= s_ut + s_accel_time_mult_05(((G_HYPERLOOP_TIMEBASE_SIZE * 2) - 1) downto 0);

						--compute current veloc.
						s_current_veloc <= s_current_accel_x1000g * s_time_base_ns;
						
						if s_coast_active = '1' then
							--start coasting
							s_sm_state <= ST_COAST;
						else
							--stay in state
							s_sm_state <= ST_ACCEL;
						end if;
		
					when ST_COAST =>
					
						if s_decel_active = '1' then
							--start decel
							s_sm_state <= ST_DECEL;
						else
							--stay in state
							s_sm_state <= ST_COAST;
						end if;
		
		
					when ST_DECEL =>
		
					when ST_STOP =>
					
			end case;
		
		end if;
	end process;
	
	--use: http://www.mobilefish.com/services/big_number/big_number.php
	
	--determine if our veloc is > a particular value for the coast phase
	--for simplicity we'll use distance
	--use 500m as displacement (500 x 10^21)
	s_coast_active <= '1' when (s_current_veloc > s_max_veloc) else '0';
	
	--decel after 750m
	s_decel_active <= '1' when (s_displacement > std_logic_vector(decimal_string_to_unsigned("750000000000000000000000", s_displacement'length)))
						else '0';
	
	--Marker List
	--A very manual list of markers based on displacement, need a big-ass FPGA for this.
	--Units of displacement are going to be fun.
	
	--Tube layout:
	--Expected distance = 1250m to 1510m
	--100ft = 30480mm
	--500ft = 152400mm
	--1000ft = 304800mm
	--1250m = 1250000mm
	--1250m - 1000ft = 945200mm (distance from start of track to 100ft mark)
	--4in = 101.6mm (grr 0.6 is an issue, lets call it 102mm)
	--Approx 31 makers between 0 and 1000ft.
	
	
	
	--Lets assume track is 1.6km
	 --Lets assume track is 1600m
        hloop_laser_o(0) <= '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("30480000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("30581600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("60960000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("61061600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("91440000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("91541600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("121920000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("122021600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("152400000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("152501600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("182880000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("182981600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("213360000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("213461600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("243840000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("243941600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("274320000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("274421600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("304800000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("304901600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("335280000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("335381600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("365760000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("365861600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("396240000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("396341600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("426720000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("426821600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("457200000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("457301600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("487680000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("487781600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("518160000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("518261600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("548640000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("548741600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("579120000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("579221600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("609600000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("609701600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("640080000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("640181600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("670560000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("670661600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("701040000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("701141600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("731520000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("731621600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("762000000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("762101600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("792480000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("792581600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("822960000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("823061600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("853440000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("853541600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("883920000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("884021600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("914400000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("914501600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("944880000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("944981600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("975360000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("975461600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1005840000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1005941600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1036320000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1036421600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1066800000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1066901600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1097280000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1097381600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1127760000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1127861600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1158240000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1158341600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1188720000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1188821600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1219200000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1219301600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1249680000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1249781600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1280160000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1280261600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1310640000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1310741600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1341120000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1341221600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1371600000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1371701600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1402080000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1402181600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1432560000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1432661600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1463040000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1463141600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1493520000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1493621600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1524000000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1524101600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1554480000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1554581600000000000000000", s_displacement'length))) ) else
                                                '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("1584960000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("1585061600000000000000000", s_displacement'length))) )

                                                else 0;
			
	--Generate the 1/2at^2 by shift
	GEN_05AT : for j in 0 to ((G_HYPERLOOP_TIMEBASE_SIZE * 4) - 2) generate
	begin
		s_accel_time_mult_05(j) <= s_accel_time_mult(j + 1);
	end generate;
	s_accel_time_mult_05((G_HYPERLOOP_TIMEBASE_SIZE * 4) - 1) <= '0';  
	
	
end architecture;
