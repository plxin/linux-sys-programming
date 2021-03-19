CPPFLAGS=
CFLAGS=
LDFLAGS= -lpthread
CC=gcc

src= $(wildcard *.c)
obj= $(patsubst *.c, *.o, $(src))
target= pthread_setattributes

$(target):$(obj)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

.PHONY:clean

clean:
	-rm -f *.o
	-rm -f $(target)
