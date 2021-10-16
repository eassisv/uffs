library IEEE;

use IEEE.STD_LOGIC_1164.ALL;

entity menor_que is
	port( s, total : in STD_LOGIC_VECTOR(7 DOWNTO 0);
		  menor : out STD_LOGIC);
menor_que;
architecture compara of menor_que is
begin
	menor <= '1' when s > total else '0';
end compara;