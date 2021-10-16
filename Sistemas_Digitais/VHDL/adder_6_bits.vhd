entity adder_6_bits is
	port(
		x, y: in bit_vector (5 downto 0);
		   z: in bit;
		   s: out bit_vector (5 downto 0);
		   vs: out bit
	);
end adder_6_bits;

architecture soma in adder_6_bits is
	component soma_1_bit
	port(
		a, b, ve:		in	bit;
		s, vs:	  out bit
		);
	end component;
	signal v: bit_vector (5 downto 1);

begin
	x0:	som_1a PORT MAP(x(0), y(0), z, s(0), v(1));
	x1:	som_1a PORT MAP(x(1), y(1), v(1), s(1), v(2));
	x2:	som_1a PORT MAP(x(2), y(2), v(2), s(2), v(3));
	x3:	som_1a PORT MAP(x(3), y(3), v(3), s(3), v(4));
	x1:	som_1a PORT MAP(x(1), y(1), v(4), s(4), v(5));
	x1:	som_1a PORT MAP(x(1), y(1), v(5), s(5), vs);
end soma;