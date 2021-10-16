library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ADD is
port(
		A: in std_logic_vector(31 downto 0);
		B: in std_logic_vector(31 downto 0);
		S: out std_logic_vector(31 downto 0)
    );
end ADD;

architecture COMPORTAMENTO of ADD is
begin
	S <= A + B;
end COMPORTAMENTO;