library IEEE;

use IEEE.STD_LOGIC_1164.ALL;

entity bc is
	port( c, rst, clk : in STD_LOGIC;
		  ctotal, rtotal, d : out STD_LOGIC);
end bc;
architecture estrutura of bc if
	type: state_type(inicio, espera, acum, libera);
	signal state : state_type;
begin
	process (clk, rst)
	begin
		if(rst = '1') then
			state <= inicio;
		elsif(clk'EVENT and clk = '1') then
			case state is
				when inicio =>
					state <= espera;
				when espera =>
					if c = '1' then state <= acum;
					elsif menor = '0' then state <= libera;
					else state <= espera;
				when acum =>
					state <= espera;
				when libera =>
					state <= inicio;
			end case;
		end if;
	end process;
	
	process (state)
	begin
		case state is
		when inicio =>
			d <= '0';
			rtotal <= '1';
			
end estrutura;