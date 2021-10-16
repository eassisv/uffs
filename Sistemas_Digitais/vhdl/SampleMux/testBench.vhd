library IEEE;

use IEEE.STD_LOGIC_1164.ALL;

entity testBench is
end testBench;

architecture BENCH of testBench is

component mux4
	port (SEL : in STD_LOGIC;
		  A, B : in STD_LOGIC;
		  X : out STD_LOGIC
	);
end component;	
	signal SEL: STD_LOGIC;
	signal A, B, X : STD_LOGIC;

begin
	SEL <= '0', '1' after 15 NS;
	A <= '0', '1' after 10 NS;
	B <= '0', '1' after 20 NS;
	M: mux4 port map(SEL, A, B, X);
end BENCH;

