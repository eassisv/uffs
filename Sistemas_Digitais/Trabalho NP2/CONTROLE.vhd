library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity CONTROLE is
    port(
      A: in std_logic_vector(5 downto 0);
      REGDEST, ALUSRC, MEMTOREG, REGWRITE, MEMREAD, MEMWRITE, BRANCH: out std_logic;
      ALU_OP: out std_logic_vector(1 downto 0)
    );
end CONTROLE;

architecture COMPORTAMENTO of CONTROLE is
begin
	process (A) begin
		case A is
			when "000000" => -- INSTRUÇÕES R-TYPE
				REGWRITE <= '1';
				REGDEST  <= '1';
				ALUSRC   <= '0';
				BRANCH   <= '0';
				MEMWRITE <= '0';
				MEMTOREG <= '0';
				ALU_OP   <= "10";
			when "100011" => -- LW
				REGDEST  <= '0';
				ALUSRC   <= '1';
				MEMTOREG <= '1';
				REGWRITE <= '1';
				MEMREAD  <= '1';
				MEMWRITE <= '0';
				BRANCH   <= '0';
				ALU_OP   <= "00";
			when "101011" => -- SW
				ALUSRC   <= '1';
				REGWRITE <= '0';
				MEMREAD  <= '0';
				MEMWRITE <= '1';
				BRANCH   <= '0';
				ALU_OP   <= "00";
			when "000100" => -- BEQ
				ALUSRC   <= '0';
				REGWRITE <= '0';
				MEMREAD  <= '0';
				MEMWRITE <= '0';
				BRANCH   <= '1';
				ALU_OP   <= "01";
			when "001000" => -- ADDI
				REGWRITE <= '1';
				REGDEST  <= '0';
				ALUSRC   <= '1';
				BRANCH   <= '0';
				MEMWRITE <= '0';
				MEMTOREG <= '0';
				ALU_OP   <= "00";
			when others => NULL;
		end case;
	end process;
end COMPORTAMENTO;