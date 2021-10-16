LIBRARY IEEE;

USE ieee.std_logic_1164.ALL;

ENTITY mealy IS
	PORT (
		Clock, Resetn, w : IN STD_LOGIC;
		z                : OUT STD_LOGIC
	);
END mealy;

ARCHITECTURE Behavior OF mealy IS
	TYPE State_type (A, B);
	SIGNAL y: State_type;
BEGIN
	PROCESS (Resetn, Clock)
	BEGIN
		IF Resetn = '0' THEN
			y <= 'A';
		ELSIF (Clock'EVENT AND Clock = '1') THEN
			CASE y IS
				WHEN A =>
					IF w = '0' THEN y <= A;
					ELSE y <= B;
					END IF;
				WHEN B =>
					IF w = '0' THEN y <= A;
					ELSE y <= B;
					END IF;
			END CASE;
		END IF;
	END PROCESS;
	PROCESS (y, w)
	BEGIN
		CASE y IS
			WHEN A =>
				z <= '0';
			WHEN B =>
				z = 'w';
		END CASE;
	END PROCESS;
END Behavior;