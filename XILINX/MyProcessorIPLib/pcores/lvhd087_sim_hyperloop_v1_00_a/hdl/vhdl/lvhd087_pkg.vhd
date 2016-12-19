library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


package lvhd087_pkg is

	function decimal_string_to_unsigned(decimal_string: string; wanted_bitwidth: positive) return unsigned;

end lvhd087_pkg;

	
package body lvhd087_pkg is

	function decimal_string_to_unsigned(decimal_string: string; wanted_bitwidth: positive) return unsigned is
	
		--have some additional bits to ensure we can handle overflows
		variable tmp_unsigned: unsigned(wanted_bitwidth + 3 downto 0) := (others => '0');
		variable character_value: integer;
	begin
	
		for string_pos in decimal_string'range loop
		case decimal_string(string_pos) is
			when '0' =>
				character_value := 0;
			when '1' =>
				character_value := 1;
			when '2' =>
				character_value := 2;
			when '3' =>
				character_value := 3;
			when '4' =>
				character_value := 4;
			when '5' =>
				character_value := 5;
			when '6' =>
				character_value := 6;
			when '7' =>
				character_value := 7;
			when '8' =>
				character_value := 8;
			when '9' =>
				character_value := 9;
			when others => report("Illegal number") severity failure;
	end case;
	tmp_unsigned := tmp_unsigned(wanted_bitwidth-1 downto 0) * to_unsigned(10, 4);
	tmp_unsigned := tmp_unsigned + character_value;
	if tmp_unsigned(wanted_bitwidth+3 downto wanted_bitwidth) /= "0000" then
	report("Too large number") severity failure;
	end if;
	end loop;
	return tmp_unsigned(wanted_bitwidth-1 downto 0);
	end decimal_string_to_unsigned;

end lvhd087_pkg;
