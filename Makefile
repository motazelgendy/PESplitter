all:
	 gcc -ggdb main.c -lcapstone -o mft
clean:
	rm -rf mft
