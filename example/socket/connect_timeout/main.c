#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

extern int connect_nonblock( int , struct sockaddr *, int, struct timeval, int * );
extern char *connect_nonblock_get_error_message( int );
 
#define TCPL_E_ERROR	(-1)
#define TCPL_S_SUCCESS	(0)
#define EHD_LOG_P2(a,b,c)	fprintf(stderr,"ERROR:%s:errno=%d\n",b,c);

static void pr_now_time(){
	struct tm *tmp;
	struct timeval tv;
 
	gettimeofday(&tv,NULL);
	tmp=localtime(&tv.tv_sec);
	printf("%04d/%02d/%02d %02d:%02d:%02d:%3d\n",
		tmp->tm_year + 1900, tmp->tm_mon + 1,
		tmp->tm_mday, tmp->tm_hour,
		tmp->tm_min, tmp->tm_sec,
		tv.tv_usec/1000);
} 

int tcpl_sck_settimeout(s, timeout)
int     s;
int     timeout;
{
#ifndef TCP_USER_TIMEOUT
	#define TCP_USER_TIMEOUT 18  // how long for loss retry before timeout [ms]
#endif
	int     status;
	int     stimeout = timeout;  // user timeout in milliseconds [ms]
	status = setsockopt (s, IPPROTO_TCP, TCP_USER_TIMEOUT, (char*) &stimeout, sizeof (stimeout));
	if (status != 0)        {
		EHD_LOG_P2 (TCPL_F_FATAL_OS ,"setsockopt (TCP_USER_TIMEOUT)", errno);
		return (TCPL_E_ERROR);
	}

	return (TCPL_S_SUCCESS);
}

#define CHECK_ERROR(ret,str)	if((ret)<0){printf("ERROR : %s :errno=%d\n",(str),errno);perror("ERROR(errno)");}

int main( int argc, char **argv )
{
    int sockfd;
    struct sockaddr_in addr;
	int i;
	int ret;
	char *adr_str = "127.0.0.1";
	int port;
	int is_block = 1;
 
	if (argc <= 3) {
		fprintf( stderr, "usage: %s ip_address port_number is_block\n", *argv );
		fprintf( stderr, "  is_block : 1..block mode / 0..non block mode\n" );
		return(1);
	}
	adr_str = argv[1];
	port = atoi( argv[2] );
	is_block = atoi( argv[3] );
    // ?????å?����
    if( (sockfd = socket( AF_INET, SOCK_STREAM, 0) ) < 0 ) {
        perror( "socket" );
    }
 
    // ?????襢?ɥ쥹???ݡ????ֹ?????
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port );
    addr.sin_addr.s_addr = inet_addr( adr_str );
 
#define TIME_OUT_SEC	5
    // ????????³
	if ( is_block ) {
		ret = tcpl_sck_settimeout(sockfd, TIME_OUT_SEC * 1000);
		CHECK_ERROR(ret,"tcpl_sck_settimeout()");
		printf( "connect( %s, %d ) timeout=%d sec\n", adr_str, port, TIME_OUT_SEC );
		pr_now_time();
		ret = connect( sockfd, (struct sockaddr *)&addr, sizeof( struct sockaddr_in ) );
		pr_now_time();
		CHECK_ERROR(ret,"connect(BLOCKING)");
	} else {
	struct timeval timeout;
	int error_id = 0;
	timeout.tv_sec = TIME_OUT_SEC; /* 5 sec */
	timeout.tv_usec = 0; /* Microseconds. */
	printf( "connect_nonblock( %s, %d ) timeout=%d sec\n", adr_str, port, TIME_OUT_SEC );
	pr_now_time();
    ret = connect_nonblock( sockfd, (struct sockaddr *)&addr, sizeof( struct sockaddr_in ), timeout, &error_id );
	pr_now_time();
	if ( ret < 0 ) {
		fprintf( stderr, "ERROR: connect_noblock() : %s : errno=%d\n", connect_nonblock_get_error_message(error_id), errno );
		if( errno ) perror("connect_nonblock");
	}
	}
 
/*
    // ?ǡ???????
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
*/ 

    close( sockfd );
 
    return 0;
}
