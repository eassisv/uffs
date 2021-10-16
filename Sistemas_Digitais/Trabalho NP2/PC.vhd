library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity PC is
    port(
      D: IN STD_LOGIC_VECTOR(31 downto 0);
      clk : IN STD_LOGIC;
      Q: OUT STD_LOGIC_VECTOR(31 downto 0)
    );
end PC;

architecture COMPORTAMENTO of PC is
begin
	process (D) begin
		if(clk'EVENT and clk = '1') then
			Q <= D;
		end if;
	end process;
end COMPORTAMENTO;