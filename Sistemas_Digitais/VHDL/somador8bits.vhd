entity somador is
	port(
		sa, sb: in bit_vector (7 downto 0);
		cout: out bit;
	);
end somador;

architecture soma of somador is

	component bgp
	port(
		prop, gen: in bit_vector (1 downto 0);
		cin: in bit;
		cout, c4: out bit
	);
	end component;
	component  somadorLah
	port(
		a, b: in bit_vector(3 downto 0);
		cin: in bit;
		s, c: out bit_vector(3 downto 0);
		prop, gen: out bit
	);
	end component;

	signal p, g: bit_vector (1 downto 0);
	
begin

	x1: somadorLah PORT MAP(sa(0), sa(1), sa(2), sa(3), sb(0), sb(1), sb(2), sb(3), '0', );
	x2: somadorLah PORT MAP(sa(4), sa(5), sa(6), sa(7), sb(4), sb(5), sb(6), sb(7), );
	
	x3: bgp PORT MAP();
	
end soma;