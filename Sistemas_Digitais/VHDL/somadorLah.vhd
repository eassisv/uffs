entity somadorLah is
	port(
		a, b: in bit_vector(3 downto 0);
		cin: in bit;
		s, c: out bit_vector(3 downto 0);
		prop, gen: out bit
		);
end somadorLah;

architecture soma of somadorLah is
	signal p, g, ors: bit_vector(3 downto 0);
	signal ands: bit_vector(9 downto 0);
begin
	p <= a XOR b;
	g <= a AND b;
	
	ands(0) <= cin AND p(0) ;
	ands(1) <= p(1) AND g(0);
	ands(2) <= cin AND p(0) AND p(1);
	ands(3) <= cin AND p(0) AND p(1) AND p(2);
	ands(4) <= p(1) AND p(2) AND g(0);
	ands(5) <= p(2) AND g(1);
	ands(6) <= g(1) AND p(2) AND p(3);
	ands(7) <= g(0) AND p(1) AND p(2) AND p(3);
	ands(8) <= g(1) AND p(3);
	ands(9) <= p(0) AND p(1) AND p(2) AND p(3);
	
	ors(0) <= ands(0) OR g(0);
	ors(1) <= ands(1) OR ands(2) OR g(1);
	ors(2) <= ands(3) OR ands(4) OR ands(5) OR g(2);
	ors(3) <= ands(6) OR ands(7) OR ands(8) OR g(3);
	
	c <= ors;
	
	s(0) <= p(0) XOR cin after 1 NS;
	s(1) <= p(1) XOR ors(0) after 1 NS;
	s(2) <= p(2) XOR ors(1) after 1 NS;
	s(3) <= p(3) XOR ors(2) after 1 NS;
	
	prop <= ands(9);
	gen <= ors(3);
	
end soma;
