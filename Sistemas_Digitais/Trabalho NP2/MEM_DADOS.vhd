library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MEM_DADOS is
    port(
        ENDE: in std_logic_vector(31 downto 0);
        DATA: in std_logic_vector(31 downto 0);
        WRITE: in std_logic;
        READ: in std_logic;
        DADO_S: out std_logic_vector(31 downto 0)
    );
end MEM_DADOS;

architecture COMPORTAMENTO of MEM_DADOS is
	type MEMORIA is array(0 to 65535) of std_logic_vector(7 downto 0);
	signal MEM: MEMORIA;
begin
    process(WRITE) is
		begin
			if(WRITE = '1') then
				MEM(conv_integer(ENDE))	    <=	DATA(31 downto 24);
				MEM(conv_integer(ENDE)+1)	<=	DATA(23 downto 16);
				MEM(conv_integer(ENDE)+2)	<=	DATA(15 downto 8);
				MEM(conv_integer(ENDE)+3)	<=	DATA(7 downto 0);
			end if;
	end process;
	DADO_S <= MEM(conv_integer(ENDE))& MEM(conv_integer(ENDE)+1)& MEM(conv_integer(ENDE)+2)& MEM(conv_integer(ENDE)+3) when READ = '1';
end COMPORTAMENTO;