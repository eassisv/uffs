add wave -position end  sim:/mips/clk
add wave -position end  sim:/mips/ENDE
add wave -position end  sim:/mips/AUX
add wave -position end  sim:/mips/SELY
add wave -position end  sim:/mips/WRITE
add wave -position end  sim:/mips/READ
add wave -position end sim:/mips/MEMP/*
add wave -position end sim:/mips/BANCO/*
add wave -position 11 sim:/mips/MEMD/*
add wave -position 0  sim:/mips/MEMD/MEM
force -freeze sim:/mips/clk 1 0, 0 {50 ps} -r 100
force -freeze sim:/mips/BANCO/MUX(0) 00000000000000000000000000000000 0
force -freeze sim:/mips/AUX 00100000000000010000000000000111 0
force -freeze sim:/mips/ENDE 00000000000000000000000000000000 0
force -freeze sim:/mips/WRITE 1 0
force -freeze sim:/mips/READ 0 0
force -freeze sim:/mips/SELY 1 0
force -freeze sim:/mips/READ 0 0
run
force -freeze sim:/mips/SELY 0 0
force -freeze sim:/mips/WRITE 0 0
force -freeze sim:/mips/READ 1 0
run
force -freeze sim:/mips/BANCO/MUX(31) 00000000000000000000000000000000 0
force -freeze sim:/mips/AUX 10101111111000010000000000000000 0
force -freeze sim:/mips/ENDE 00000000000000000000000000000100 0
force -freeze sim:/mips/SELY 1 0
force -freeze sim:/mips/WRITE 1 0
force -freeze sim:/mips/READ 0 0
run
force -freeze sim:/mips/SELY 0 0
force -freeze sim:/mips/WRITE 0 0
force -freeze sim:/mips/READ 1 0
run