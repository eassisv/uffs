library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DECOD is
    port(
        A: in std_logic_vector(31 downto 0);
        CONT: out std_logic_vector(5 downto 0);
        RS, RT, RDI, RDR: out std_logic_vector(4 downto 0);
        CONST: out std_logic_vector(15 downto 0);
        OP_ULA: out std_logic_vector(5 downto 0)
	);
end DECOD;

architecture COMPORTAMENTO of DECOD is
begin
	CONT <= A(31 downto 26);
	RS <= A(25 downto 21);
	RT <= A(20 downto 16);
	RDR <= A(15 downto 11);
	RDI <= A(20 downto 16);
	CONST <= A(15 downto 0);
	OP_ULA <= A(5 downto 0);
end COMPORTAMENTO;
