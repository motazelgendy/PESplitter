all:
	 gcc -ggdb main.c -lopdis -lbfd -lopcodes -o mft
clean:
	rm -rf mft
