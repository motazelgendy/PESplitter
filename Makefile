all:
	 gcc -ggdb main.c -lopdis -lbfd -lopcodes -lcapstone -o mft
clean:
	rm -rf mft
