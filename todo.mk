todo: todoclient.o todofunc.o
	gcc todoclient.o todofunc.o

todofunc.o: todofunc.c todohead.h
			gcc -c todofunc.c

todoclient.o: todoclient.c todohead.h
			gcc -c todoclient.c
