library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity AND_2 is
    port(
        A: IN std_logic;
        B: IN std_logic;
        S: OUT std_logic
    );
end AND_2;

architecture COMPORTAMENTO of AND_2 is
begin
	S <= A and B;
end COMPORTAMENTO;	