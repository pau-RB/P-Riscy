

core:
	bsc -simdir SIM -vdir V  -bdir build -aggressive-conditions -u ./Core.bsv

clean:
	rm -f ./build/*.bo