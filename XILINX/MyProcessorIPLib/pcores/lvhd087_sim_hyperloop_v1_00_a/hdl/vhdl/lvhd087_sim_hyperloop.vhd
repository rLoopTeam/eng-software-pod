

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library lvhd022_xilinx_proc_common_v3_00_a;
use lvhd022_xilinx_proc_common_v3_00_a.proc_common_pkg.all;
use lvhd022_xilinx_proc_common_v3_00_a.ipif_pkg.all;

library lvhd031_xilinx_plbv46_slave_single_v1_01_a;
use lvhd031_xilinx_plbv46_slave_single_v1_01_a.plbv46_slave_single;

library lvhd087_sim_hyperloop_v1_00_a;
use lvhd087_sim_hyperloop_v1_00_a.user_logic;


entity lvhd087_sim_hyperloop is
	generic
	(
		--! The number of laser outputs
		G_HYPERLOOP_NUM_LASERS : integer := 1;
		C_SPLB_CLK_FREQ_HZ : integer := 100_000_000;
	
	
		-- DO NOT EDIT BELOW THIS LINE ---------------------
		-- Bus protocol parameters, do not add to or delete
		C_BASEADDR : std_logic_vector := X"FFFFFFFF";
		C_HIGHADDR : std_logic_vector := X"00000000";
		C_SPLB_AWIDTH : integer := 32;
		C_SPLB_DWIDTH : integer	 := 128;
		C_SPLB_NUM_MASTERS : integer := 8;
		C_SPLB_MID_WIDTH : integer := 3;
		C_SPLB_NATIVE_DWIDTH : integer := 32;
		C_SPLB_P2P : integer := 0;
		C_SPLB_SUPPORT_BURSTS : integer := 0;
		C_SPLB_SMALLEST_MASTER : integer := 32;
		C_SPLB_CLK_PERIOD_PS : integer := 10000;
		C_INCLUDE_DPHASE_TIMER : integer := 0;
		C_FAMILY : string := "virtex6"
		-- DO NOT EDIT ABOVE THIS LINE ---------------------
	);
 port
 (
		--! the laser output
		hloop_laser_o : out std_logic_vector((G_HYPERLOOP_NUM_LASERS - 1) downto 0);
		
		--! Start/stop debug signal
		hloop_start_o : out std_logic;
		
		--! Timing Clock
		hloop_clk_i : in std_logic;

		-- DO NOT EDIT BELOW THIS LINE ---------------------
		-- Bus protocol ports, do not add to or delete
		SPLB_Clk					 : in std_logic;
		SPLB_Rst					 : in std_logic;
		PLB_ABus					 : in std_logic_vector(0 to 31);
		PLB_UABus					 : in std_logic_vector(0 to 31);
		PLB_PAValid					: in std_logic;
		PLB_SAValid					: in std_logic;
		PLB_rdPrim					 : in std_logic;
		PLB_wrPrim					 : in std_logic;
		PLB_masterID				 : in std_logic_vector(0 to C_SPLB_MID_WIDTH-1);
		PLB_abort					 : in std_logic;
		PLB_busLock					: in std_logic;
		PLB_RNW						: in std_logic;
		PLB_BE						 : in std_logic_vector(0 to C_SPLB_DWIDTH/8-1);
		PLB_MSize					 : in std_logic_vector(0 to 1);
		PLB_size					 : in std_logic_vector(0 to 3);
		PLB_type					 : in std_logic_vector(0 to 2);
		PLB_lockErr					: in std_logic;
		PLB_wrDBus					 : in std_logic_vector(0 to C_SPLB_DWIDTH-1);
		PLB_wrBurst					: in std_logic;
		PLB_rdBurst					: in std_logic;
		PLB_wrPendReq				 : in std_logic;
		PLB_rdPendReq				 : in std_logic;
		PLB_wrPendPri				 : in std_logic_vector(0 to 1);
		PLB_rdPendPri				 : in std_logic_vector(0 to 1);
		PLB_reqPri					 : in std_logic_vector(0 to 1);
		PLB_TAttribute				 : in std_logic_vector(0 to 15);
		Sl_addrAck					 : out std_logic;
		Sl_SSize					 : out std_logic_vector(0 to 1);
		Sl_wait						: out std_logic;
		Sl_rearbitrate				 : out std_logic;
		Sl_wrDAck					 : out std_logic;
		Sl_wrComp					 : out std_logic;
		Sl_wrBTerm					 : out std_logic;
		Sl_rdDBus					 : out std_logic_vector(0 to C_SPLB_DWIDTH-1);
		Sl_rdWdAddr					: out std_logic_vector(0 to 3);
		Sl_rdDAck					 : out std_logic;
		Sl_rdComp					 : out std_logic;
		Sl_rdBTerm					 : out std_logic;
		Sl_MBusy					 : out std_logic_vector(0 to C_SPLB_NUM_MASTERS-1);
		Sl_MWrErr					 : out std_logic_vector(0 to C_SPLB_NUM_MASTERS-1);
		Sl_MRdErr					 : out std_logic_vector(0 to C_SPLB_NUM_MASTERS-1);
		Sl_MIRQ						: out std_logic_vector(0 to C_SPLB_NUM_MASTERS-1)
		-- DO NOT EDIT ABOVE THIS LINE ---------------------
 );

 attribute MAX_FANOUT : string;
 attribute SIGIS : string;

 attribute SIGIS of SPLB_Clk	 : signal is "CLK";
 attribute SIGIS of SPLB_Rst	 : signal is "RST";

end entity lvhd087_sim_hyperloop;

------------------------------------------------------------------------------
-- Architecture section
------------------------------------------------------------------------------

architecture IMP of lvhd087_sim_hyperloop is

	------------------------------------------
	-- Array of base/high address pairs for each address range
	------------------------------------------
	constant ZERO_ADDR_PAD : std_logic_vector(0 to 31) := (others => '0');
	constant USER_SLV_BASEADDR : std_logic_vector := C_BASEADDR;
	constant USER_SLV_HIGHADDR : std_logic_vector := C_HIGHADDR;

	constant IPIF_ARD_ADDR_RANGE_ARRAY : SLV64_ARRAY_TYPE := 
	(
		ZERO_ADDR_PAD & USER_SLV_BASEADDR, -- user logic slave space base address
		ZERO_ADDR_PAD & USER_SLV_HIGHADDR -- user logic slave space high address
	);

	------------------------------------------
	-- Array of desired number of chip enables for each address range
	------------------------------------------
	constant USER_SLV_NUM_REG : integer := 16;
	constant USER_NUM_REG : integer := USER_SLV_NUM_REG;

	constant IPIF_ARD_NUM_CE_ARRAY : INTEGER_ARRAY_TYPE := 
	(
		0 => pad_power2(USER_SLV_NUM_REG) -- number of ce for user logic slave space
	);

	------------------------------------------
	-- Ratio of bus clock to core clock (for use in dual clock systems)
	-- 1 = ratio is 1:1
	-- 2 = ratio is 2:1
	------------------------------------------
	constant IPIF_BUS2CORE_CLK_RATIO: integer := 1;

	------------------------------------------
	-- Width of the slave data bus (32 only)
	------------------------------------------
	constant USER_SLV_DWIDTH: integer := C_SPLB_NATIVE_DWIDTH;

	constant IPIF_SLV_DWIDTH: integer := C_SPLB_NATIVE_DWIDTH;

	------------------------------------------
	-- Index for CS/CE
	------------------------------------------
	constant USER_SLV_CS_INDEX : integer := 0;
	constant USER_SLV_CE_INDEX : integer := calc_start_ce_index(IPIF_ARD_NUM_CE_ARRAY, USER_SLV_CS_INDEX);

	constant USER_CE_INDEX : integer := USER_SLV_CE_INDEX;

	------------------------------------------
	-- IP Interconnect (IPIC) signal declarations
	------------------------------------------
	signal ipif_Bus2IP_Clk: std_logic;
	signal ipif_Bus2IP_Reset : std_logic;
	signal ipif_IP2Bus_Data : std_logic_vector(0 to IPIF_SLV_DWIDTH-1);
	signal ipif_IP2Bus_WrAck : std_logic;
	signal ipif_IP2Bus_RdAck : std_logic;
	signal ipif_IP2Bus_Error : std_logic;
	signal ipif_Bus2IP_Addr : std_logic_vector(0 to C_SPLB_AWIDTH-1);
	signal ipif_Bus2IP_Data : std_logic_vector(0 to IPIF_SLV_DWIDTH-1);
	signal ipif_Bus2IP_RNW: std_logic;
	signal ipif_Bus2IP_BE : std_logic_vector(0 to IPIF_SLV_DWIDTH/8-1);
	signal ipif_Bus2IP_CS : std_logic_vector(0 to ((IPIF_ARD_ADDR_RANGE_ARRAY'length)/2)-1);
	signal ipif_Bus2IP_RdCE : std_logic_vector(0 to calc_num_ce(IPIF_ARD_NUM_CE_ARRAY)-1);
	signal ipif_Bus2IP_WrCE : std_logic_vector(0 to calc_num_ce(IPIF_ARD_NUM_CE_ARRAY)-1);
	signal user_Bus2IP_RdCE : std_logic_vector(0 to USER_NUM_REG-1);
	signal user_Bus2IP_WrCE : std_logic_vector(0 to USER_NUM_REG-1);
	signal user_IP2Bus_Data : std_logic_vector(0 to USER_SLV_DWIDTH-1);
	signal user_IP2Bus_RdAck : std_logic;
	signal user_IP2Bus_WrAck : std_logic;
	signal user_IP2Bus_Error : std_logic;

	begin

	------------------------------------------
	-- instantiate plbv46_slave_single
	------------------------------------------
	PLBV46_SLAVE_SINGLE_I : entity lvhd031_xilinx_plbv46_slave_single_v1_01_a.plbv46_slave_single
	generic map
	(
		C_ARD_ADDR_RANGE_ARRAY => IPIF_ARD_ADDR_RANGE_ARRAY,
		C_ARD_NUM_CE_ARRAY => IPIF_ARD_NUM_CE_ARRAY,
		C_SPLB_P2P => C_SPLB_P2P,
		C_BUS2CORE_CLK_RATIO => IPIF_BUS2CORE_CLK_RATIO,
		C_SPLB_MID_WIDTH => C_SPLB_MID_WIDTH,
		C_SPLB_NUM_MASTERS => C_SPLB_NUM_MASTERS,
		C_SPLB_AWIDTH => C_SPLB_AWIDTH,
		C_SPLB_DWIDTH => C_SPLB_DWIDTH,
		C_SIPIF_DWIDTH => IPIF_SLV_DWIDTH,
		C_INCLUDE_DPHASE_TIMER => C_INCLUDE_DPHASE_TIMER,
		C_FAMILY => C_FAMILY
	)
	port map
	(
		SPLB_Clk => SPLB_Clk,
		SPLB_Rst => SPLB_Rst,
		PLB_ABus => PLB_ABus,
		PLB_UABus => PLB_UABus,
		PLB_PAValid=> PLB_PAValid,
		PLB_SAValid=> PLB_SAValid,
		PLB_rdPrim => PLB_rdPrim,
		PLB_wrPrim => PLB_wrPrim,
		PLB_masterID => PLB_masterID,
		PLB_abort => PLB_abort,
		PLB_busLock=> PLB_busLock,
		PLB_RNW=> PLB_RNW,
		PLB_BE => PLB_BE,
		PLB_MSize => PLB_MSize,
		PLB_size => PLB_size,
		PLB_type => PLB_type,
		PLB_lockErr=> PLB_lockErr,
		PLB_wrDBus => PLB_wrDBus,
		PLB_wrBurst=> PLB_wrBurst,
		PLB_rdBurst=> PLB_rdBurst,
		PLB_wrPendReq => PLB_wrPendReq,
		PLB_rdPendReq => PLB_rdPendReq,
		PLB_wrPendPri => PLB_wrPendPri,
		PLB_rdPendPri => PLB_rdPendPri,
		PLB_reqPri => PLB_reqPri,
		PLB_TAttribute => PLB_TAttribute,
		Sl_addrAck => Sl_addrAck,
		Sl_SSize => Sl_SSize,
		Sl_wait=> Sl_wait,
		Sl_rearbitrate => Sl_rearbitrate,
		Sl_wrDAck => Sl_wrDAck,
		Sl_wrComp => Sl_wrComp,
		Sl_wrBTerm => Sl_wrBTerm,
		Sl_rdDBus => Sl_rdDBus,
		Sl_rdWdAddr=> Sl_rdWdAddr,
		Sl_rdDAck => Sl_rdDAck,
		Sl_rdComp => Sl_rdComp,
		Sl_rdBTerm => Sl_rdBTerm,
		Sl_MBusy => Sl_MBusy,
		Sl_MWrErr => Sl_MWrErr,
		Sl_MRdErr => Sl_MRdErr,
		Sl_MIRQ=> Sl_MIRQ,
		Bus2IP_Clk => ipif_Bus2IP_Clk,
		Bus2IP_Reset => ipif_Bus2IP_Reset,
		IP2Bus_Data=> ipif_IP2Bus_Data,
		IP2Bus_WrAck => ipif_IP2Bus_WrAck,
		IP2Bus_RdAck => ipif_IP2Bus_RdAck,
		IP2Bus_Error => ipif_IP2Bus_Error,
		Bus2IP_Addr=> ipif_Bus2IP_Addr,
		Bus2IP_Data=> ipif_Bus2IP_Data,
		Bus2IP_RNW => ipif_Bus2IP_RNW,
		Bus2IP_BE => ipif_Bus2IP_BE,
		Bus2IP_CS => ipif_Bus2IP_CS,
		Bus2IP_RdCE=> ipif_Bus2IP_RdCE,
		Bus2IP_WrCE=> ipif_Bus2IP_WrCE
	);

	------------------------------------------
	-- instantiate User Logic
	------------------------------------------
	USER_LOGIC_I : entity lvhd087_sim_hyperloop_v1_00_a.user_logic
	generic map
	(
		G_HYPERLOOP_NUM_LASERS => G_HYPERLOOP_NUM_LASERS,
		C_SPLB_CLK_FREQ_HZ => C_SPLB_CLK_FREQ_HZ,
		C_SLV_DWIDTH => USER_SLV_DWIDTH,
		C_NUM_REG => USER_NUM_REG,
		C_FAMILY => C_FAMILY
	)
	port map
	(
		--our laser channel
		hloop_laser_o => hloop_laser_o,
		hloop_start_o => hloop_start_o,
		hloop_clk_i => hloop_clk_i,
		
		Bus2IP_Clk => ipif_Bus2IP_Clk,
		Bus2IP_Reset => ipif_Bus2IP_Reset,
		Bus2IP_Data=> ipif_Bus2IP_Data,
		Bus2IP_BE => ipif_Bus2IP_BE,
		Bus2IP_RdCE=> user_Bus2IP_RdCE,
		Bus2IP_WrCE=> user_Bus2IP_WrCE,
		IP2Bus_Data=> user_IP2Bus_Data,
		IP2Bus_RdAck => user_IP2Bus_RdAck,
		IP2Bus_WrAck => user_IP2Bus_WrAck,
		IP2Bus_Error => user_IP2Bus_Error
	);

	------------------------------------------
	-- connect internal signals
	------------------------------------------
	ipif_IP2Bus_Data <= user_IP2Bus_Data;
	ipif_IP2Bus_WrAck <= user_IP2Bus_WrAck;
	ipif_IP2Bus_RdAck <= user_IP2Bus_RdAck;
	ipif_IP2Bus_Error <= user_IP2Bus_Error;

	user_Bus2IP_RdCE <= ipif_Bus2IP_RdCE(USER_CE_INDEX to USER_CE_INDEX+USER_NUM_REG-1);
	user_Bus2IP_WrCE <= ipif_Bus2IP_WrCE(USER_CE_INDEX to USER_CE_INDEX+USER_NUM_REG-1);

end IMP;
