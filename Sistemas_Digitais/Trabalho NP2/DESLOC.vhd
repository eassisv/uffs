library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DESLOC is
    port(
        A: in std_logic_vector(31 downto 0);
        S: out std_logic_vector(31 downto 0)
    );
end DESLOC;

architecture COMPORTAMENTO of DESLOC is
begin
	S <= A (29 downto 0) & "00";
end COMPORTAMENTO;