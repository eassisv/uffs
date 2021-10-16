entity soma_1_bit is
port(a, b, ve		:		in	bit;
	  s, vs			:	  out bit);
end som_1a;

architecture somador of soma_1_bit is
begin
		b = b XOR ve;
		s  <= a XOR (b XOR ve) after 5 NS;                        -- soma
		vs <= (a AND b) OR (a AND ve) OR (b AND ve) after 5 NS; -- vai um
end somador;