library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity OP_ULA is
    port(
      A: in std_logic_vector(1 downto 0);
      B: in std_logic_vector(5 downto 0);
      S: out std_logic_vector(2 downto 0)
    );
end OP_ULA;

architecture COMPORTAMENTO of OP_ULA is
begin
	process (A, B) is
	begin
		case a is
		when "10"=> 		
			case B is
			when "100000" => -- ADD
				S <= "010";
			when "101010" => -- SLT
				S <= "111";
			when others => NULL;
			end case;
		when "00" => S <= "010";
		when "01" => S <= "110";
		when others => NULL;
		end case;
	end process;
end COMPORTAMENTO;