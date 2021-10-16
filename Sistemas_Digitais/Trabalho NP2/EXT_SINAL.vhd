library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity EXT_SINAL is
    port(
        A: in std_logic_vector(15 downto 0);
        S: out std_logic_vector(31 downto 0)
    );
end EXT_SINAL;

architecture COMPORTAMENTO of EXT_SINAL is
begin
	process (A) begin
		if A(15) = '1' then
			S <= "1111111111111111" & A;
		else
			S <= "0000000000000000" & A;
		end if;
	end process;
end COMPORTAMENTO;