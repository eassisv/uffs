entity testBench is
end testBench;

architecture soma of testBench if
	component adder_6_bits;
		port(
			x, y: in bit_vector (5 downto 0);
		    z: in bit;
		    s: out bit_vector (5 downto 0);
		    vs: out bit
		);
	end component;

	signal vx: bit_vector (5 downto 0);
	
begin
	x(0) <= '1' after 1 NS;
	y(0) <= '1' after 1 NS;
end soma;