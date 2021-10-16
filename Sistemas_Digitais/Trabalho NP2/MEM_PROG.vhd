library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity MEM_PROG is
  port(
    ENDE, DATA: in std_logic_vector(31 downto 0);
    WRITE, READ: in std_logic;
    INST: out std_logic_vector(31 downto 0)
  );
end MEM_PROG;

architecture comportamento of MEM_PROG is
	type memoria is array(0 to 65535) of std_logic_vector(7 downto 0);
	signal mem: memoria;
begin
    process(write) is
		begin
			if(write='1') then
				mem(conv_integer(ENDE))	    <=	DATA(31 downto 24);
				mem(conv_integer(ENDE)+1)	<=	DATA(23 downto 16);
				mem(conv_integer(ENDE)+2)	<=	DATA(15 downto 8);
				mem(conv_integer(ENDE)+3)	<=	DATA(7 downto 0);
			end if;
	end process;
	INST<=mem(conv_integer(ENDE))&mem(conv_integer(ENDE)+1)&mem(conv_integer(ENDE)+2)&mem(conv_integer(ENDE)+3) when read='1';
end comportamento;