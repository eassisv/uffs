library IEEE;

use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_SIGNED.ALL;

entity somador is
	port( t, a : in STD_LOGIC_VECTOR(7 DOWNTO 0);
		  res : out STD_LOGIC_VECTOR(7 DOWNTO 0));
end somador;
architecture soma of somador is
begin
	res <= t + a;
end soma;