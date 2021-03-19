CPPFLAGS= -Iinclude
CFLAGS= -g -Wall
CC= gcc

src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
target = main

$(target): $(obj)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $< $(CFLAGS) $(CPPFLAGS) -o $@

.PHONY:clean

clean:
	-rm -f *.o $(target)
