library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ULA is
    port(
      A: in std_logic_vector(31 downto 0);
      B: in std_logic_vector(31 downto 0);
      SEL: in std_logic_vector(2 downto 0);
      zero: out std_logic;
      S: out std_logic_vector(31 downto 0)
    );
end ULA;

architecture COMPORTAMENTO of ULA is
begin
	process (A, B, SEL) begin
		case SEL is
			when "010" => S <= A  +  B;
			when "111" => 
				if (conv_integer(A) < conv_integer(B)) then
					S <= "00000000000000000000000000000001";
				else
					S <= "00000000000000000000000000000000";
				end if;
			when others => NULL;
		end case;
		if (A = B) then
			zero <= '1';
		else
			zero <= '0';
		end if;
	end process;
end COMPORTAMENTO;
