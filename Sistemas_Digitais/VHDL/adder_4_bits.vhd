entity adder_4_bits is													-- Declaraçao da entidade
port(x,y		:	in		bit_vector(3 downto 0);						-- Entradas do somador
	  ze		:	in		bit;												-- "vem um"
	  s		: out		bit_vector(3 downto 0);						-- Soma
	  zs		: out		bit);												-- "vai um"
end adder_4_bits;															-- Final da declaraçao da entidade

architecture hardware of adder_4_bits is							-- Declaração da arquitetura

	component som_1a														-- Declaraçao do componente
	port(a,b,ve		:		in		bit;									-- entradas
		  s,vs		:	  out		bit);									-- saidas
	end component;															-- Final da declaração do componente
	
	signal v		: bit_vector(3 downto 1);							-- Sinal interno "vai um"
	
begin

	x0:	som_1a	PORT MAP(      x(0),      y(0),      ze,         s(0),       v(1));
	x1:   som_1a   PORT MAP(      x(1),      y(1),      v(1),       s(1),       v(2));
	x2:   som_1a   PORT MAP(      x(2),      y(2),      v(2),       s(2),       v(3));
	x3:   som_1a   PORT MAP(      x(3),      y(3),      v(3),       s(3),        zs );
	
end hardware;