all : main main.pthread

main : sample_pthread_attr_setschedparam.c
	cc -o $@ $<

main.pthread : sample_pthread_attr_setschedparam.c
	cc -pthread -o $@ $<

clean :
	rm -f main main.pthread

