entity bgp is
	port(
			prop, gen: in bit_vector (1 downto 0);
			cin: in bit;
			cout, c4: out bit
			);
end bgp;

architecture hardware of bgp is
	signal ands: bit_vector(2 downto 0);
	signal ors: bit_vector(2 downto 1);
begin
	ands(0) <= cin AND prop(0);
	ands(1) <= gen(0) AND prop(1);
	ands(2) <= cin AND prop(1) AND prop(0);
	ors(1) <= gen(0) OR ands(0);
	ors(2) <= ands(1) OR ands(2) OR gen(1);
	cout <= ors(2);
	c4 <= ors(1);
end hardware;