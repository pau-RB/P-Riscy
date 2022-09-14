

backend:
	bsc -bdir build -aggressive-conditions -u ./backend.bsv

clean:
	rm -f ./build/*.bo