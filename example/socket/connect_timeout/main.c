#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

extern int connect_nonblock( int , struct sockaddr *, int, struct timeval, int * );
extern char* connect_nonblock_get_error_message( int );
 
int main( int argc, char **argv )
{
	int sockfd;
	struct sockaddr_in addr;
	int i;
	int ret;
	char *adr_str = "127.0.0.1";
	int port;
 
	if (argc < 2) {
		fprintf( stderr, "usage: %s ip_address port_number\n", *argv );
		return(1);
	}
	adr_str = argv[1];
	port = atoi( argv[2] );
	if( (sockfd = socket( AF_INET, SOCK_STREAM, 0) ) < 0 ) {
		perror( "socket" );
	}
 
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	addr.sin_addr.s_addr = inet_addr( adr_str );
 
	struct timeval timeout;
	int error_id = 0;
	timeout.tv_sec = 5; /* 5 sec */
	timeout.tv_usec = 0; /* Microseconds. */
	printf( "connect_nonblock( %s, %d )\n", adr_str, port );
	ret = connect_nonblock( sockfd, (struct sockaddr *)&addr, sizeof( struct sockaddr_in ), timeout, &error_id );
	if ( ret < 0 ) {
		fprintf( stderr, "ERROR: connect_noblock() : %s : errno=%d\n", connect_nonblock_get_error_message(error_id), errno );
		if( errno ) perror("connect_nonblock");
		return(1);
	}
 
	char send_str[10];
	char receive_str[10];
	for ( i = 0; i < 10; i++ ){
		sprintf( send_str, "%d", i );
		printf( "send:%d\n", i );
		if( send( sockfd, send_str, 10, 0 ) < 0 ) {
			perror( "send" );
		} else {
			recv( sockfd, receive_str, 10, 0 );
			printf( "receive:%s\n", receive_str );
		}
		sleep( 1 );
	}
 
	close( sockfd );
 
	return 0;
}
