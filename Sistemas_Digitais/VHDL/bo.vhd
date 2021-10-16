library IEEE;

use IEEE.STD_LOGIC_1164.ALL;

entity bo is
	port( clk, Ctotal, Rtotal : in STD_LOGIC;
		  s, a : in STD_LOGIC_VECTOR (7 DOWNTO 0);
		  menor : out STD_LOGIC );
end bo;
architecture estrutura of bo is
	signal soma, total : STD_LOGIC_VECTOR(7 DOWNTO 0);
begin
	reg : registrador port map (clk, Ctotal, Rtotal, soma, total);
	som : somador port map(total, a, soma);
	men : menor_que port map(s, total);
end estrutura;