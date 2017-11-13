all: todo clean

todo: todoclient.o todofunc.o
	gcc -o todo todoclient.o todofunc.o

todofunc.o: todofunc.c todohead.h
			gcc -c todofunc.c

todoclient.o: todoclient.c todohead.h
			gcc -c todoclient.c

clean:
	rm -f *.o
