all:server client

server: server.c wrap.c
	gcc $^ -o $@

client: client.c wrap.c
	gcc $^ -o $@

.PHONY:clean

clean:
	-rm -f server
	-rm -f client
