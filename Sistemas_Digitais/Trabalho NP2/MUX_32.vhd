library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MUX_32 is
    port(
        A: in std_logic_vector(31 downto 0);
        B: in std_logic_vector(31 downto 0);
        SEL : in std_logic;
        S: out std_logic_vector(31 downto 0)
    );
end MUX_32;

architecture COMPORTAMENTO of MUX_32 is
begin
	process (A, B, SEL) begin
		if sel = '0' then
			S <= A;
		else
			S <= B;
		end if;
	end process;
end COMPORTAMENTO;