library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity B_R is
    port(
        clk: in std_logic;
        REG_WRITE: in std_logic;
        RS, RD, RT: in std_logic_vector(4 downto 0);
        DADO_WRITE: in std_logic_vector(31 downto 0);
        DL1, DL2: out std_logic_vector(31 downto 0)
    );
end B_R;

architecture COMPORTAMENTO of B_R is

	type MUX_REG is array(31 downto 0) of std_logic_vector(31 downto 0);
	signal MUX: MUX_REG;

begin
	process (RS, RD, RT) begin
		if (clk'EVENT and clk = '1') then
			DL1 <= MUX(conv_integer(RS));
			DL2 <= MUX(conv_integer(RT));
		end if;			
	end process;
	MUX(conv_integer(RD)) <= DADO_WRITE when REG_WRITE = '1';
end COMPORTAMENTO;
