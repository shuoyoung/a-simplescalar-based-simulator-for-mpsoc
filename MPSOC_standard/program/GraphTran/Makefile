CC=mips_4KCle-gcc
CFLAGS=-g3 -O3 -static -w
G:G.o API.o
	$(CC) $(CFLAGS) API.o G.o -o G.elf -lm
G.o:G.c
	$(CC) $(CFLAGS) -c G.c
API.o:API.s
	$(CC) $(CFLAGS) -c API.s
clean:
	rm -rf *.o *.elf *~
