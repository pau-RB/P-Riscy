

backend:
	bsc -simdir SIM -vdir V  -bdir build -aggressive-conditions -u ./backend.bsv

clean:
	rm -f ./build/*.bo