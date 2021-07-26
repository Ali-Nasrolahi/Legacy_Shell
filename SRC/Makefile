CC=clang
CFLAGS=

Legacy_Shell: LShell.o
	$(CC) $(CFLAGS)  LShell.o -o $@ 

LShell.o: LShell.c
	$(CC) $(CFLAGS) -c LShell.c

clean:
	$(RM) *.o  Legacy_Shell	