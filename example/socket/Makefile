
allexe = server client printip

all : $(allexe)

clean :
	rm -f $(allexe)

server : server.c
	cc -g -o server server.c

printip : printip.c
	cc -g -o printip printip.c

client : client.c
	cc -o client client.c
