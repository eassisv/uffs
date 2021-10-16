library IEEE;

use IEEE.STD_LOGIC_1164.ALL;

entity registrador is
	port( clk, carga, reset : in STD_LOGIC;
	      s : in STD_LOGIC_VECTOR(7 DOWNTO 0);
		  total : out STD_LOGIC_VECTOR(7 DOWNTO 0));
end reg;

architecture registra of reg is
begin
	process(clk, reset)
	begin
		if(reset = '1') then
			total <= 00000000;
		elsif(clk'EVENT and clk = '1' and carga = '1') then
			total <= s;
		end if
	end process
end registra;