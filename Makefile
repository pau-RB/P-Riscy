
verilog:
	bsc -simdir SIM -vdir V -bdir build -verilog -g mkCore5S -aggressive-conditions -u ./Core.bsv

core:
	bsc -simdir SIM -vdir V -bdir build -aggressive-conditions -u ./Core.bsv

clean:
	rm -f ./build/*.bo
	rm -f ./V/*.v